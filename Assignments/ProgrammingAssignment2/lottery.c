#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/percpu.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/random.h>
#include <linux/workqueue.h>
#include <linux/smp.h>
#include <linux/cpu.h>
#include <linux/atomic.h>
#include <linux/capability.h>
#include "lottery.h"

#define QUANTUM_MS 50
#define HYSTERESIS_TICKETS 50
#define OVERSHOOT_TOLERANCE 20

struct lottery_entry {
    struct list_head link;
    struct task_struct *task;
    pid_t pid;
    unsigned long tickets;
};

struct lottery_rq {
    spinlock_t lock;
    struct list_head tasks;
    unsigned long total_tickets;
    unsigned int task_count;
};

static struct lottery_rq __percpu *runqueues;
static struct delayed_work scheduler_work;
static atomic_t tick_count = ATOMIC_INIT(0);
static bool stopping;

static struct lottery_rq *rq_for_cpu(int cpu)
{
    return per_cpu_ptr(runqueues, cpu);
}

static int queue_task(int cpu, struct lottery_entry *entry)
{
    struct lottery_rq *rq = rq_for_cpu(cpu);
    unsigned long flags;
    struct lottery_entry *it;

    spin_lock_irqsave(&rq->lock, flags);
    list_for_each_entry(it, &rq->tasks, link) {
        if (it->pid == entry->pid) {
            spin_unlock_irqrestore(&rq->lock, flags);
            return -EEXIST;
        }
    }
    list_add_tail(&entry->link, &rq->tasks);
    rq->total_tickets += entry->tickets;
    rq->task_count++;
    spin_unlock_irqrestore(&rq->lock, flags);
    return 0;
}

static long lottery_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct lottery_struct request;
    struct pid *pid_ref;
    struct task_struct *task;
    struct lottery_entry *entry, *it;
    int cpu, best_cpu = -1, err = 0;
    unsigned long best_tickets = ULONG_MAX, flags;

    if (copy_from_user(&request, (void __user *)arg, sizeof(request)))
        return -EFAULT;
    if (!request.pid || request.pid > PID_MAX_LIMIT)
        return -EINVAL;

    if (cmd == LOTTERY_REGISTER) {
        if (request.pid != (unsigned long)task_pid_nr(current) || !request.tickets)
            return -EINVAL;
        entry = kzalloc(sizeof(*entry), GFP_KERNEL);
        if (!entry)
            return -ENOMEM;
        pid_ref = find_get_pid((pid_t)request.pid);
        task = pid_ref ? get_pid_task(pid_ref, PIDTYPE_PID) : NULL;
        if (pid_ref)
            put_pid(pid_ref);
        if (!task) {
            kfree(entry);
            return -ESRCH;
        }
        entry->task = task; /* get_pid_task() supplies a task reference */
        entry->pid = (pid_t)request.pid;
        entry->tickets = request.tickets;
        INIT_LIST_HEAD(&entry->link);

        for_each_online_cpu(cpu) {
            struct lottery_rq *rq = rq_for_cpu(cpu);
            spin_lock_irqsave(&rq->lock, flags);
            if (rq->total_tickets < best_tickets) {
                best_tickets = rq->total_tickets;
                best_cpu = cpu;
            }
            spin_unlock_irqrestore(&rq->lock, flags);
        }
        if (best_cpu < 0) {
            put_task_struct(task);
            kfree(entry);
            return -ENODEV;
        }
        err = set_cpus_allowed_ptr(task, cpumask_of(best_cpu));
        if (!err)
            err = queue_task(best_cpu, entry);
        if (err) {
            put_task_struct(task);
            kfree(entry);
            return err;
        }
        pr_info("[LOTTERY] Registered PID %d with %lu tickets on CPU %d\n",
                entry->pid, entry->tickets, best_cpu);
        return 0;
    }

    if (cmd == LOTTERY_UNREGISTER) {
        if (request.pid != (unsigned long)task_pid_nr(current))
            return -EINVAL;
        for_each_possible_cpu(cpu) {
            struct lottery_rq *rq = rq_for_cpu(cpu);
            spin_lock_irqsave(&rq->lock, flags);
            list_for_each_entry(it, &rq->tasks, link) {
                if (it->pid == (pid_t)request.pid) {
                    list_del(&it->link);
                    rq->total_tickets -= it->tickets;
                    rq->task_count--;
                    spin_unlock_irqrestore(&rq->lock, flags);
                    put_task_struct(it->task);
                    kfree(it);
                    return 0;
                }
            }
            spin_unlock_irqrestore(&rq->lock, flags);
        }
        return -ENOENT;
    }
    return -ENOTTY;
}

static const struct file_operations lottery_fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = lottery_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = lottery_ioctl,
#endif
};

static struct miscdevice lottery_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "lottery",
    .fops = &lottery_fops,
    .mode = 0666,
};

static void balance_queues(void)
{
    int src = -1, dst = -1, cpu;
    unsigned long max = 0, min = ULONG_MAX, flags1, flags2;
    struct lottery_rq *from, *to;
    struct lottery_entry *entry, *chosen = NULL;
    struct task_struct *chosen_task = NULL;
    pid_t chosen_pid = 0;
    unsigned long chosen_tickets = 0;

    for_each_online_cpu(cpu) {
        struct lottery_rq *rq = rq_for_cpu(cpu);
        unsigned long flags;
        unsigned long load;
        spin_lock_irqsave(&rq->lock, flags);
        load = rq->total_tickets;
        spin_unlock_irqrestore(&rq->lock, flags);
        if (load > max) { max = load; src = cpu; }
        if (load < min) { min = load; dst = cpu; }
    }
    if (src < 0 || dst < 0 || src == dst || max <= min + HYSTERESIS_TICKETS)
        return;

    from = rq_for_cpu(src);
    to = rq_for_cpu(dst);
    if (src < dst) {
        spin_lock_irqsave(&from->lock, flags1);
        spin_lock_irqsave_nested(&to->lock, flags2, SINGLE_DEPTH_NESTING);
    } else {
        spin_lock_irqsave(&to->lock, flags1);
        spin_lock_irqsave_nested(&from->lock, flags2, SINGLE_DEPTH_NESTING);
    }
    if (from->total_tickets > to->total_tickets + HYSTERESIS_TICKETS) {
        list_for_each_entry(entry, &from->tasks, link) {
            if (to->total_tickets + entry->tickets <=
                from->total_tickets - entry->tickets + OVERSHOOT_TOLERANCE) {
                chosen = entry;
                break;
            }
        }
        if (chosen) {
            get_task_struct(chosen->task);
            chosen_task = chosen->task;
            chosen_pid = chosen->pid;
            chosen_tickets = chosen->tickets;
            list_move_tail(&chosen->link, &to->tasks);
            from->total_tickets -= chosen->tickets;
            from->task_count--;
            to->total_tickets += chosen->tickets;
            to->task_count++;
        }
    }
    if (src < dst) {
        spin_unlock_irqrestore(&to->lock, flags2);
        spin_unlock_irqrestore(&from->lock, flags1);
    } else {
        spin_unlock_irqrestore(&from->lock, flags2);
        spin_unlock_irqrestore(&to->lock, flags1);
    }
    if (chosen_task) {
        int ret = set_cpus_allowed_ptr(chosen_task, cpumask_of(dst));
        if (!ret)
            pr_info("[LOTTERY] Load Balance: Migrated PID %d (%lu tix) CPU %d -> CPU %d\n",
                    chosen_pid, chosen_tickets, src, dst);
        put_task_struct(chosen_task);
    }
}

static void apply_lottery(void)
{
    int cpu;
    for_each_online_cpu(cpu) {
        struct lottery_rq *rq = rq_for_cpu(cpu);
        struct lottery_entry *entry;
        struct task_struct *winner_task = NULL;
        struct task_struct **tasks;
        unsigned int n = 0, i = 0;
        unsigned long flags, draw, cumulative = 0, total;

        spin_lock_irqsave(&rq->lock, flags);
        total = rq->total_tickets;
        list_for_each_entry(entry, &rq->tasks, link)
            n++;
        spin_unlock_irqrestore(&rq->lock, flags);

        tasks = kcalloc(n, sizeof(*tasks), GFP_KERNEL);
        if (n && !tasks)
            continue;

        spin_lock_irqsave(&rq->lock, flags);
        total = rq->total_tickets;
        if (total) {
            get_random_bytes(&draw, sizeof(draw));
            draw = draw % total + 1;
            list_for_each_entry(entry, &rq->tasks, link) {
                cumulative += entry->tickets;
                if (draw <= cumulative) {
                    winner_task = entry->task;
                    get_task_struct(winner_task);
                    break;
                }
            }
        }
        list_for_each_entry(entry, &rq->tasks, link) {
            if (i == n)
                break;
            get_task_struct(entry->task);
            tasks[i++] = entry->task;
        }
        spin_unlock_irqrestore(&rq->lock, flags);
        /* Keep signal delivery outside the runqueue lock. */
        for (i = 0; i < n; i++) {
            if (tasks[i] != winner_task)
                send_sig(SIGSTOP, tasks[i], 1);
            put_task_struct(tasks[i]);
        }
        if (winner_task) {
            send_sig(SIGCONT, winner_task, 1);
            put_task_struct(winner_task);
        }
        kfree(tasks);
    }
}

static void report_status(void)
{
    char line[512];
    size_t used = 0;
    int cpu;
    for_each_online_cpu(cpu) {
        struct lottery_rq *rq = rq_for_cpu(cpu);
        unsigned long flags, tickets;
        unsigned int count;
        spin_lock_irqsave(&rq->lock, flags);
        tickets = rq->total_tickets;
        count = rq->task_count;
        spin_unlock_irqrestore(&rq->lock, flags);
        used += scnprintf(line + used, sizeof(line) - used,
                          "CPU%d: %lu tix (%u tasks) | ", cpu, tickets, count);
    }
    pr_info("[LOTTERY_STATUS] %s\n", line);
}

static void scheduler_tick(struct work_struct *work)
{
    if (READ_ONCE(stopping))
        return;
    balance_queues();
    apply_lottery();
    if (atomic_inc_return(&tick_count) % 10 == 0)
        report_status();
    schedule_delayed_work(&scheduler_work, msecs_to_jiffies(QUANTUM_MS));
}

static int __init lottery_init(void)
{
    int cpu, ret;
    runqueues = alloc_percpu(struct lottery_rq);
    if (!runqueues)
        return -ENOMEM;
    for_each_possible_cpu(cpu) {
        struct lottery_rq *rq = rq_for_cpu(cpu);
        spin_lock_init(&rq->lock);
        INIT_LIST_HEAD(&rq->tasks);
        rq->total_tickets = 0;
        rq->task_count = 0;
    }
    ret = misc_register(&lottery_device);
    if (ret) {
        free_percpu(runqueues);
        return ret;
    }
    INIT_DELAYED_WORK(&scheduler_work, scheduler_tick);
    schedule_delayed_work(&scheduler_work, msecs_to_jiffies(QUANTUM_MS));
    pr_info("lottery: loaded with %u online CPUs\n", num_online_cpus());
    return 0;
}

static void __exit lottery_exit(void)
{
    int cpu;
    WRITE_ONCE(stopping, true);
    cancel_delayed_work_sync(&scheduler_work);
    misc_deregister(&lottery_device);
    for_each_possible_cpu(cpu) {
        struct lottery_rq *rq = rq_for_cpu(cpu);
        struct lottery_entry *entry, *tmp;
        unsigned long flags;
        spin_lock_irqsave(&rq->lock, flags);
        list_for_each_entry_safe(entry, tmp, &rq->tasks, link) {
            list_del(&entry->link);
            send_sig(SIGCONT, entry->task, 1);
            put_task_struct(entry->task);
            kfree(entry);
        }
        rq->total_tickets = 0;
        rq->task_count = 0;
        spin_unlock_irqrestore(&rq->lock, flags);
    }
    free_percpu(runqueues);
    pr_info("lottery: unloaded\n");
}

module_init(lottery_init);
module_exit(lottery_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Zhu");
MODULE_DESCRIPTION("Lottery scheduler");
