ifeq ($(strip $(ARCH)),)
ARCH = nspire
endif
include arch-$(ARCH)/$(ARCH).mk

DEBUG = FALSE
ifeq ($(DEBUG),FALSE)
	GCCFLAGS += -O3
else
	GCCFLAGS += -O0 -g
	LDFLAGS += --debug
endif

GCCFLAGS += -DNSPIREIO_BUILD -Wall -Werror -Wextra

CPPOBJS = $(patsubst %.cpp,%.o,$(wildcard common/cpp/*.cpp))
OBJS = $(patsubst %.c,%.o,$(wildcard common/*.c)) $(patsubst %.c,%.o,$(wildcard arch-$(ARCH)/*.c)) $(CPPOBJS)

LIB = libnspireio.a

.PHONY: all lib clean install uninstall demo

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o: %.cpp
	$(GXX) $(GCCFLAGS) -c $< -o $@
	
%.o: %.S
	$(AS) -c $< -o $@

all: demo

lib: $(LIB)

$(LIB): $(OBJS)
	mkdir -p lib
	$(AR) rcs "lib/$(LIB)" $^

demo: $(LIB)
	mkdir -p bin
	+make -C demo/adv ARCH=$(ARCH)
	+make -C demo/compatibility ARCH=$(ARCH)
	+make -C demo/hello ARCH=$(ARCH)
	+make -C demo/splitscreen ARCH=$(ARCH)
	+make -C demo/tests ARCH=$(ARCH)
	+make -C demo/cplusplus ARCH=$(ARCH)
	
install: $(LIB)
	mkdir -p "$(DESTDIR)/include/nspireio"
	cp include/nspireio2.h "$(DESTDIR)/include/nspireio2.h"
	cp include/nspireio/* "$(DESTDIR)/include/nspireio"
	cp lib/$(LIB) "$(DESTDIR)/lib"
	
uninstall:
	rm -rf "$(DESTDIR)/include/nspireio" "$(DESTDIR)/lib/$(LIB)" "$(DESTDIR)/include/nspireio2.h"

clean:
	rm -f $(wildcard */*.o) $(wildcard common/cpp/*.o) *.elf lib/$(LIB)
	+make -C demo/adv ARCH=$(ARCH) clean
	+make -C demo/compatibility ARCH=$(ARCH) clean
	+make -C demo/hello ARCH=$(ARCH) clean
	+make -C demo/splitscreen ARCH=$(ARCH) clean
	+make -C demo/tests ARCH=$(ARCH) clean
	+make -C demo/cplusplus ARCH=$(ARCH) clean
	
