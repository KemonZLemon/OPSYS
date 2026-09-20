// SPDX-License-Identifier: GPL-2.0
/*
 * reboot_guard.c - Require a passphrase for reboot(2) restart requests.
 *
 * The probe runs before the kernel's reboot implementation.  A rejected
 * request is redirected back to the syscall dispatcher with -EINVAL, without
 * reaching the kernel reboot implementation.
 */

#include <linux/cred.h>
#include <linux/errno.h>
#include <linux/kprobes.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/uaccess.h>

#define REBOOT_PASSPHRASE "Passphrase"
#define PASSPHRASE_MAX_LEN 128

#if defined(__x86_64__)
#define REBOOT_SYSCALL_SYMBOL "__x64_sys_reboot"
/* The syscall wrapper receives a pt_regs pointer in its first C argument. */
#define SYSCALL_REGS(probe_regs) ((struct pt_regs *)(probe_regs)->di)
#define SYSCALL_ARG4(probe_regs) \
	((const char __user *)SYSCALL_REGS(probe_regs)->r10)
#define REJECT_REBOOT(probe_regs) do { \
	(probe_regs)->ax = -EINVAL; \
	(probe_regs)->ip = *(unsigned long *)(probe_regs)->sp; \
	(probe_regs)->sp += sizeof(unsigned long); \
} while (0)
#elif defined(__aarch64__)
#define REBOOT_SYSCALL_SYMBOL "__arm64_sys_reboot"
#define SYSCALL_REGS(probe_regs) ((struct pt_regs *)(probe_regs)->regs[0])
#define SYSCALL_ARG4(probe_regs) \
	((const char __user *)SYSCALL_REGS(probe_regs)->regs[3])
#define REJECT_REBOOT(probe_regs) do { \
	(probe_regs)->regs[0] = -EINVAL; \
	(probe_regs)->pc = (probe_regs)->regs[30]; \
} while (0)
#else
#error "reboot_guard supports only x86_64 and arm64"
#endif

static bool passphrase_is_valid(const char __user *user_passphrase)
{
	char passphrase[PASSPHRASE_MAX_LEN];
	long copied;

	if (!user_passphrase)
		return false;

	/* Copy at most one complete user-space C string into kernel memory. */
	copied = strncpy_from_user(passphrase, user_passphrase,
				   sizeof(passphrase));
	if (copied < 0 || copied == sizeof(passphrase))
		return false;

	passphrase[copied] = '\0';
	return strcmp(passphrase, REBOOT_PASSPHRASE) == 0;
}

static int reboot_guard_pre_handler(struct kprobe *probe,
				    struct pt_regs *probe_regs)
{
	const char __user *user_passphrase = SYSCALL_ARG4(probe_regs);

	(void)probe;

	if (passphrase_is_valid(user_passphrase)) {
		pr_info("reboot_guard: reboot authorized for %s (pid=%d uid=%u)\n",
			current->comm, current->pid, __kuid_val(current_uid()));
		return 0;
	}

	pr_warn("reboot_guard: authentication failed for %s (pid=%d uid=%u); rejecting reboot\n",
		current->comm, current->pid, __kuid_val(current_uid()));

	/*
	 * A non-zero pre-handler return tells kprobes that we changed the execution
	 * path.  The adjusted registers emulate a function return of -EINVAL.
	 */
	REJECT_REBOOT(probe_regs);
	return 1;
}

static struct kprobe reboot_probe = {
	.symbol_name = REBOOT_SYSCALL_SYMBOL,
	.pre_handler = reboot_guard_pre_handler,
};

static int __init reboot_guard_init(void)
{
	int ret;

	ret = register_kprobe(&reboot_probe);
	if (ret) {
		pr_err("reboot_guard: could not probe %s: %d\n",
		       REBOOT_SYSCALL_SYMBOL, ret);
		return ret;
	}

	pr_info("reboot_guard: loaded; reboot passphrase protection enabled\n");
	return 0;
}

static void __exit reboot_guard_exit(void)
{
	unregister_kprobe(&reboot_probe);
	pr_info("reboot_guard: unloaded\n");
}

module_init(reboot_guard_init);
module_exit(reboot_guard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OPSYS student");
MODULE_DESCRIPTION("Passphrase guard for the reboot system call");
