savedcmd_pagecacheTest.mod := printf '%s\n'   pagecacheTest.o | awk '!x[$$0]++ { print("./"$$0) }' > pagecacheTest.mod
