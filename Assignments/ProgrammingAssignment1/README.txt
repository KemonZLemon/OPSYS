Programming Assignment 1: Authenticated Reboot System Call Guard

Implementation
--------------
reboot_guard.c is a GPL Linux kernel module that registers a kprobe on the
architecture-specific reboot syscall wrapper (__x64_sys_reboot on x86_64 and
__arm64_sys_reboot on arm64).  The probe obtains the fourth syscall argument,
copies the user-space C string with strncpy_from_user(), and compares it in
kernel space with the module's passphrase.  A match is logged with pr_info()
and the reboot syscall is allowed to continue.  A missing, unreadable,
oversized, or incorrect passphrase is logged with pr_warn(); the probe then
redirects execution to return -EINVAL before reboot handling occurs.

reboot_auth.c is a pass-through user-space program.  It passes argv[1]
directly as the fourth argument of SYS_reboot, or passes NULL when no argument
is supplied.  It contains no passphrase or local validation logic.

The Makefile builds reboot_guard.ko and reboot_auth with the running Linux
kernel's build directory and C compiler, respectively.


1. Missing passphrase
   Command: sudo ./reboot_auth
   Expected result: The client reports a reboot error, the system remains up,
   andrecords an authentication-failed.
2. Incorrect passphrase
   Command: sudo ./reboot_auth "WRONG_PASSPHRASE"
   Expected result: The client reports a reboot error, the system remains up,
   and records an authentication-failed.

3. Correct passphrase
   Command: sudo ./reboot_auth "Correct Passphrase"
   Expected result: Records an authorization message and the reboot
   syscall proceeds, restarting the system.
