AR := "$(shell (which arm-elf-ar arm-none-eabi-ar arm-linux-gnueabi-ar | head -1) 2>/dev/null)"
GCC = nspire-gcc
GCCFLAGS = -Os -nostdlib -g -D_TINSPIRE
LD = nspire-ld
LDFLAGS = -nostdlib
OBJCOPY := "$(shell (which arm-elf-objcopy arm-none-eabi-objcopy arm-linux-gnueabi-objcopy | head -1) 2>/dev/null)"
USERPROFILE ?= $(HOME)
DESTDIR = $(USERPROFILE)/.ndless
