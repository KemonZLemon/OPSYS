savedcmd_lottery.mod := printf '%s\n'   lottery.o | awk '!x[$$0]++ { print("./"$$0) }' > lottery.mod
