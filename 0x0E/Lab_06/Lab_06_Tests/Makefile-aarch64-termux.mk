CC = clang


CFLAGS = -O0 -Wall -std=gnu99
LDFLAGS = -L. -static
INC = -I.. 


SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

LCUNIT = libcunit-termux.a
PROJOBJ = ../Lab_06_AArch64/Matrix.o ../Lab_06_AArch64/MatrixIO.o

OUTFILE = Lab_06_Tests

all: $(SOURCES) $(PROJOBJ) $(OBJECTS) $(OUTFILE)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS) $(PROJOBJ)
	$(CC) $(OBJECTS) $(PROJOBJ) $(LCUNIT) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)

