#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/pagemap.h>
#include <linux/sched/signal.h>
#include <linux/pid.h>
#include <linux/highmem.h>
#include <linux/err.h>

#define PROC_NAME "pagecache_test"
#define INPUT_SIZE 512
#define FILE_NAME_SIZE 256

static ssize_t pagecache_test_write(struct file *file,
                                    const char __user *buffer,
                                    size_t count,
                                    loff_t *position)
{
    char input[INPUT_SIZE];
    char filename[FILE_NAME_SIZE];
    int pid_number;
    unsigned long user_address;
    struct pid *pid_ref = NULL;
    struct task_struct *task = NULL;
    struct mm_struct *mm = NULL;
    struct page *user_page = NULL;
    struct page *cache_page = NULL;
    struct file *input_file = NULL;
    struct address_space *mapping;
    void *user_map = NULL;
    void *cache_map = NULL;
    long pinned;
    unsigned long user_pfn, cache_pfn;
    int comparison;
    int i;
    ssize_t result = count;

    if (count == 0 || count >= sizeof(input))
        return -EINVAL;
    if (copy_from_user(input, buffer, count))
        return -EFAULT;
    input[count] = '\0';

    if (sscanf(input, "%d %lx %255s", &pid_number, &user_address, filename) != 3 ||
        pid_number <= 0 || user_address == 0) {
        pr_err("pagecache_test: expected PID ADDRESS FILE\n");
        return -EINVAL;
    }

    pid_ref = find_get_pid(pid_number);
    if (!pid_ref) {
        result = -ESRCH;
        goto out;
    }
    task = get_pid_task(pid_ref, PIDTYPE_PID);
    put_pid(pid_ref);
    pid_ref = NULL;
    if (!task) {
        result = -ESRCH;
        goto out;
    }
    mm = get_task_mm(task);
    if (!mm) {
        result = -EINVAL;
        goto out;
    }

    mmap_read_lock(mm);
    pinned = get_user_pages_remote(mm, user_address, 1, FOLL_GET,
                                   &user_page, NULL);
    mmap_read_unlock(mm);
    if (pinned != 1) {
        pr_err("pagecache_test: get_user_pages_remote failed: %ld\n", pinned);
        result = pinned < 0 ? pinned : -EFAULT;
        goto out;
    }

    input_file = filp_open(filename, O_RDONLY | O_LARGEFILE, 0);
    if (IS_ERR(input_file)) {
        result = PTR_ERR(input_file);
        input_file = NULL;
        goto out;
    }
    mapping = file_inode(input_file)->i_mapping;
    cache_page = find_get_page(mapping, 0);
    if (!cache_page) {
        pr_err("pagecache_test: file page 0 is not in the page cache\n");
        result = -ENOENT;
        goto out;
    }

    user_pfn = page_to_pfn(user_page);
    cache_pfn = page_to_pfn(cache_page);
    user_map = kmap_local_page(user_page);
    cache_map = kmap_local_page(cache_page);

    pr_info("========================================\n");
    pr_info("Page Cache vs User Buffer Experiment\n");
    pr_info("========================================\n");
    pr_info("PID:              %d\n", pid_number);
    pr_info("User virtual addr: 0x%lx\n", user_address);
    pr_info("File:             %s\n\n", filename);
    pr_info("USER BUFFER:\n");
    pr_info("  virtual address = 0x%lx\n", user_address);
    pr_info("  PFN              = %lu\n", user_pfn);
    pr_info("  physical address = 0x%llx\n",
            (unsigned long long)user_pfn << PAGE_SHIFT);
    pr_info("  first 16 bytes   =");
    for (i = 0; i < 16; i++)
        pr_cont(" %02x", ((unsigned char *)user_map)[i]);
    pr_cont("\n\n");

    pr_info("PAGE CACHE:\n");
    pr_info("  file offset      = 0\n");
    pr_info("  PFN              = %lu\n", cache_pfn);
    pr_info("  physical address = 0x%llx\n",
            (unsigned long long)cache_pfn << PAGE_SHIFT);
    pr_info("  first 16 bytes   =");
    for (i = 0; i < 16; i++)
        pr_cont(" %02x", ((unsigned char *)cache_map)[i]);
    pr_cont("\n\n");

    comparison = memcmp(user_map, cache_map, PAGE_SIZE);
    pr_info("memcmp(PAGE_SIZE) = %d\n", comparison);
    pr_info("========================================\n");

out:
    if (cache_map)
        kunmap_local(cache_map);
    if (user_map)
        kunmap_local(user_map);
    if (cache_page)
        put_page(cache_page);
    if (input_file)
        filp_close(input_file, NULL);
    if (user_page)
        put_page(user_page);
    if (mm)
        mmput(mm);
    if (task)
        put_task_struct(task);
    if (pid_ref)
        put_pid(pid_ref);
    return result;
}

static const struct proc_ops pagecache_test_ops = {
    .proc_write = pagecache_test_write,
};

static int __init pagecache_test_init(void)
{
    if (!proc_create(PROC_NAME, 0666, NULL, &pagecache_test_ops))
        return -ENOMEM;
    pr_info("pagecache_test: loaded\n");
    pr_info("Use /proc/%s to run the experiment\n", PROC_NAME);
    return 0;
}

static void __exit pagecache_test_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    pr_info("pagecache_test: unloaded\n");
}

module_init(pagecache_test_init);
module_exit(pagecache_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Zhu");
MODULE_DESCRIPTION("Progamming Assignment 3");
