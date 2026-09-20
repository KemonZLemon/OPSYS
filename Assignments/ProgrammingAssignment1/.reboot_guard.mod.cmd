savedcmd_reboot_guard.mod := printf '%s\n'   reboot_guard.o | awk '!x[$$0]++ { print("./"$$0) }' > reboot_guard.mod
