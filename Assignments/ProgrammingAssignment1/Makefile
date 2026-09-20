# Kernel module to build.
obj-m += reboot_guard.o

# User-space client to build.
USER_APP := reboot_auth
KDIR ?= /lib/modules/$(shell uname -r)/build
MODULE_DIR := $(CURDIR)

.PHONY: all module client clean

all: module client

module:
	$(MAKE) -C $(KDIR) M=$(MODULE_DIR) modules

client: $(USER_APP)

$(USER_APP): reboot_auth.c
	$(CC) -Wall -Wextra -O2 $< -o $@

clean:
	$(MAKE) -C $(KDIR) M=$(MODULE_DIR) clean
	$(RM) $(USER_APP)
