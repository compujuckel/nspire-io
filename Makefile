ifeq ($(strip $(ARCH)),)
ARCH = nspire
endif
include $(ARCH).mk

LIB = libnspireio.a
vpath %.a $(DESTDIR)
OBJS = console.o registry.o $(ARCH)-uart.o cursor.o $(ARCH).o

.PHONY: all lib demo install uninstall clean

all: lib

demo:
	make -C demo/adv ARCH=$(ARCH)
	make -C demo/compatibility ARCH=$(ARCH)
	make -C demo/hello ARCH=$(ARCH)
	make -C demo/replace-stdio ARCH=$(ARCH)
	make -C demo/splitscreen ARCH=$(ARCH)
	make -C demo/tests ARCH=$(ARCH)
	
lib: $(LIB)
	
%.o: %.c
	$(GCC) -DBUILDLIB $(GCCFLAGS) -c $<

%.elf: %.o
	$(LD) $(LDFLAGS) $^ -o $@

$(LIB): $(OBJS)
	$(AR) rcs "$(LIB)" $^

install:
	cp -u nspireio2.h "$(DESTDIR)/include"
	cp -u nspireio.h "$(DESTDIR)/include"
	cp -u nspireio-platform.h "$(DESTDIR)/include"
	cp -u nspireio-platform-$(ARCH).h "$(DESTDIR)/include"
	cp -u $(LIB) "$(DESTDIR)/lib/"

uninstall:
	rm -f "$(DESTDIR)/lib/$(LIB)" "$(DESTDIR)/include/nspireio2.h" "$(DESTDIR)/include/nspireio.h" "$(DESTDIR)/include/nspireio-platform.h" "$(DESTDIR)/include/nspireio-platform-$(ARCH).h"

clean:
	rm -rf *.o *.elf *.a
	rm -f $(LIB)
	make -C demo/adv ARCH=$(ARCH) clean
	make -C demo/compatibility ARCH=$(ARCH) clean
	make -C demo/hello ARCH=$(ARCH) clean
	make -C demo/replace-stdio ARCH=$(ARCH) clean
	make -C demo/splitscreen ARCH=$(ARCH) clean
	make -C demo/tests ARCH=$(ARCH) clean
