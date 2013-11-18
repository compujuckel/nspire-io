ifeq ($(strip $(FXCGSDK)),)
export FXCGSDK := $(abspath ../../../)
endif
include $(FXCGSDK)/toolchain/prizm_rules
AR = sh3eb-elf-ar
GCC = sh3eb-elf-gcc
GCCFLAGS = $(MACHDEP) -I$(FXCGSDK)/include -Wl,-static -Wl,-gc-sections -lc -lfxcg -lgcc -DPRIZM
LD = sh3eb-elf-ld
LDFLAGS = $(MACHDEP) -T$(FXCGSDK)/toolchain/prizm.x -Wl,-static -Wl,-gc-sections
OBJCOPY = sh3eb-elf-objcopy
DESTDIR = $(FXCGSDK)
