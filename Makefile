AR := "$(shell (which arm-elf-ar arm-none-eabi-ar arm-linux-gnueabi-ar | head -1) 2>/dev/null)"
GCC = nspire-gcc
GCCFLAGS = -Os -nostdlib -g
LD = nspire-ld
LDFLAGS = -nostdlib
OBJCOPY := "$(shell (which arm-elf-objcopy arm-none-eabi-objcopy arm-linux-gnueabi-objcopy | head -1) 2>/dev/null)"
LIB = libnspireio2.a
USERPROFILE ?= $(HOME)
DESTDIR = $(USERPROFILE)/.ndless
vpath %.a $(DISTDIR)
OBJS = console.o screen.o registry.o uart.o cursor.o

.PHONY: all lib demo install uninstall clean

all: lib demo

demo:
	make -C demo/adv
	make -C demo/compatibility
	make -C demo/hello
	make -C demo/replace-stdio
	make -C demo/splitscreen
	make -C demo/tests
	
lib: $(LIB)
	
%.o: %.c
	$(GCC) $(GCCFLAGS) -c $<

%.elf: %.o
	$(LD) $(LDFLAGS) $^ -o $@

$(LIB): $(OBJS)
	$(AR) rcs "$(LIB)" $^

install:
	cp -u nspireio2.h "$(DESTDIR)/include"
	cp -u $(LIB) "$(DESTDIR)/lib"

uninstall:
	rm -f "$(DESTDIR)/lib/$(LIB)" "$(DESTDIR)/include/nspireio2.h"

clean:
	rm -rf *.o *.elf *.a
	rm -f $(LIB)
	make -C demo/adv clean
	make -C demo/compatibility clean
	make -C demo/hello clean
	make -C demo/replace-stdio clean
	make -C demo/splitscreen clean
