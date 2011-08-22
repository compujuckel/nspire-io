NDLESS_PATH = SET THIS VALUE
AR := "$(shell (which arm-elf-ar arm-none-eabi-ar arm-linux-gnueabi-ar | head -1) 2>/dev/null)"
GCC = nspire-gcc
GCCFLAGS = -Os -nostdlib
LD = nspire-ld
LDFLAGS = -nostdlib
OBJCOPY := "$(shell (which arm-elf-objcopy arm-none-eabi-objcopy arm-linux-gnueabi-objcopy | head -1) 2>/dev/null)"
LIB = libnspireio.a
DISTDIR = $(NDLESS_PATH)/lib
vpath %.a $(DISTDIR)
OBJS = console.o screen.o

all: static $(LIB)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $<

%.elf: %.o
	$(LD) $(LDFLAGS) $^ -o $@

static:
	@mkdir -p $(DISTDIR)
	
$(LIB): $(OBJS)
	$(AR) rcs $(DISTDIR)/$(LIB) $^
	cp -u nspireio.h $(NDLESS_PATH)/include/nspireio.h

clean:
	rm -rf *.o *.elf *.a
	rm -f $(DISTDIR)/$(LIB)
	rm -f $(NDLESS_PATH)/include/nspireio.h
