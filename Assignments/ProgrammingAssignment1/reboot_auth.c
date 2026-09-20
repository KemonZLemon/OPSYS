/*
 * reboot_auth.c - Minimal pass-through client for reboot_guard.
 *
 * Usage: ./reboot_auth <passphrase>
 */

#include <linux/reboot.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/* With no argument, deliberately pass NULL to the kernel. */
	const char *passphrase = argc > 1 ? argv[1] : NULL;
	long result;

	result = syscall(SYS_reboot,
			 LINUX_REBOOT_MAGIC1,
			 LINUX_REBOOT_MAGIC2,
			 LINUX_REBOOT_CMD_RESTART,
			 passphrase);
	if (result == -1) {
		perror("reboot_auth: reboot failed");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
