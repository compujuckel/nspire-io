GCC = nspire-gcc
GXX = nspire-g++
LD = nspire-ld-bflt
GCCFLAGS = -Os -Wall -W -marm
LDFLAGS = 
EXE = niostream.tns
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
DISTDIR = .
vpath %.tns $(DISTDIR)

all: $(EXE)
	
%.o: %.cpp
	$(GXX) $(GCCFLAGS) -c $<

$(EXE): $(OBJS)
	mkdir -p $(DISTDIR)
	$(LD) --cpp $^ -o $(DISTDIR)/$@ $(LDFLAGS)

clean:
	rm -f *.o *.elf
	rm -f $(DISTDIR)/$(EXE)
