CC = aarch64-linux-gnu-gcc


CFLAGS = -O0 -Wall -std=gnu99
LDFLAGS = -static
INC = -I.. 


SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

LCUNIT = libcunit-aarch64.a
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

