AR := "$(shell (which arm-elf-ar arm-none-eabi-ar arm-linux-gnueabi-ar | head -1) 2>/dev/null)"
GCC = nspire-gcc
GCCFLAGS = -Os -nostdlib
LD = nspire-ld
LDFLAGS = -nostdlib
OBJCOPY := "$(shell (which arm-elf-objcopy arm-none-eabi-objcopy arm-linux-gnueabi-objcopy | head -1) 2>/dev/null)"
LIB = libnspireio2.a
DISTDIR = $(USERPROFILE)/.ndless/lib
vpath %.a $(DISTDIR)
OBJS = console.o screen.o registry.o uart.o

all: $(LIB)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $<

%.elf: %.o
	$(LD) $(LDFLAGS) $^ -o $@

$(LIB): $(OBJS)
	$(AR) rcs "$(DISTDIR)/$(LIB)" $^
	cp -u nspireio2.h "${USERPROFILE}/.ndless/include"

clean:
	rm -rf *.o *.elf *.a
	rm -f $(DISTDIR)/$(LIB)
	rm -f "${USERPROFILE}/.ndless/include/nspireio.h"
