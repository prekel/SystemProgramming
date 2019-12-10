CC = gcc



CFLAGS = -O0 -g -Wall -std=gnu99 -m32
LDFLAGS = ../Lab_06_i386/Matrix.o -lcunit -m32 -static
INC = -I.. 



SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_06_Tests

all: $(SOURCES) $(OUTFILE)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)

