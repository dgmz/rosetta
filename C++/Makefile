CC = gcc

TARGETS = lesson00 lesson01-1 lesson01-2 lesson01-3 lesson01-4 lesson01-6 wftest

all: $(TARGETS)

clean:
	rm -f *.o lesson*.tga $(TARGETS)

lesson00: lesson00.cc lib/tga.cc

lesson01-1: lesson01-1.cc lib/tga.cc

lesson01-2: lesson01-2.cc lib/tga.cc

lesson01-3: lesson01-3.cc lib/tga.cc

lesson01-4: lesson01-4.cc lib/tga.cc

lesson01-6: lesson01-6.cc lib/tga.cc lib/wavefront.cc

wftest: wftest.cc lib/wavefront.cc
