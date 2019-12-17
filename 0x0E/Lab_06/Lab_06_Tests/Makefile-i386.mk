CC = gcc


CFLAGS = -O0 -Wall -std=gnu99 -m32
LDFLAGS = -m32
INC = -I.. -I.


SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

LCUNIT = -L./CUnit/i386 -lcunit
PROJOBJ = ../Lab_06_i386-gas/Matrix.o ../Lab_06_i386-gas/MatrixIO.o

OUTFILE = Lab_06_Tests

all: $(SOURCES) $(PROJOBJ) $(OBJECTS) $(OUTFILE)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS) $(PROJOBJ)
	$(CC) $(OBJECTS) $(PROJOBJ) $(LCUNIT) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OUTFILE) $(OBJECTS)
