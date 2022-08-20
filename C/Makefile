CC = gcc

TARGETS = lesson00 lesson01-1 lesson01-2 lesson01-3 lesson01-4 lesson01-5 wftest

all: $(TARGETS)

clean:
	rm -f *.o lesson*.tga $(TARGETS)

lesson00: lesson00.c lib/tga.c

lesson01-1: lesson01-1.c lib/tga.c

lesson01-2: lesson01-2.c lib/tga.c

lesson01-3: lesson01-3.c lib/tga.c

lesson01-4: lesson01-4.c lib/tga.c

lesson01-5: lesson01-5.c lib/tga.c lib/wavefront.c

wftest: wftest.c lib/wavefront.c
