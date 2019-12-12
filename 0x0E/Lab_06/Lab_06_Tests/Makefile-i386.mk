CC = gcc


CFLAGS = -O0 -Wall -std=gnu99 -m32
LDFLAGS = -m32 -static
INC = -I.. 


SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

LCUNIT = libcunit-i386.a
PROJOBJ = ../Lab_06_i386/Matrix.o ../Lab_06_i386/MatrixIO.o

OUTFILE = Lab_06_Tests

all: $(SOURCES) $(PROJOBJ) $(OBJECTS) $(OUTFILE)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(PROJOBJ) $(LCUNIT) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)

