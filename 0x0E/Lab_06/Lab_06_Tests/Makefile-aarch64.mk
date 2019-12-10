CC = aarch64-linux-gnu-gcc


CFLAGS = -O0 -g -Wall -std=gnu99
LDFLAGS = -lcunit -static
INC = -I.. 


SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

PROJOBJ = ../Lab_06_AArch64/Matrix.o ../Lab_06_AArch64/MatrixIO.o

OUTFILE = Lab_06_Tests

all: $(SOURCES) $(OUTFILE) $(PROJOBJ)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS) $(PROJOBJ)
	$(CC) $(OBJECTS) $(PROJOBJ) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)

