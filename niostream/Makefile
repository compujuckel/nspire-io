GCC = nspire-gcc
GXX=nspire-g++
LD = nspire-ld-bflt
GCCFLAGS = -Os -Wall -W -marm -DBUILDLIB -I.
LDFLAGS = -lnspireio
CPPOBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJS = $(patsubst %.c,%.o,$(wildcard *.c)) $(CPPOBJS)
ifneq (${CPPOBJS},"")
	LDFLAGS += --cpp
endif
OBJCOPY := "$(shell which arm-elf-objcopy 2>/dev/null)"
ifeq (${OBJCOPY},"")
	OBJCOPY := arm-none-eabi-objcopy
endif
USERPROFILE ?= $(HOME)
DESTDIR = $(USERPROFILE)/.ndless
LIB = libniostream.a
vpath %.a $(DESTDIR)

.PHONY: all lib demo install uninstall clean

all: lib

lib: $(LIB)

demo:
	make -C demo/

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $<

%.o: %.cpp
	$(GXX) $(GCCFLAGS) -c $<
	
$(LIB): $(OBJS)
	$(AR) rcs "$(LIB)" $^

install:
	mkdir -p "$(DESTDIR)/include/niostream"
	cp -u console.hpp "$(DESTDIR)/include/niostream/"
	cp -u ios_base.hpp "$(DESTDIR)/include/niostream/"
	cp -u $(LIB) "$(DESTDIR)/lib/"

uninstall:
	rm -rf "$(DESTDIR)/lib/$(LIB)" "$(DESTDIR)/include/niostream"
	
clean:
	rm -f *.o *.elf *.a
	make -C demo/ clean