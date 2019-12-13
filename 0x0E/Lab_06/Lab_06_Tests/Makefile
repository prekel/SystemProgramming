CC = gcc


CFLAGS = -O0 -Wall -std=gnu99
LDFLAGS = -no-pie 
INC = -I..


SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

LCUNIT = -lcunit
PROJOBJ = ../Lab_06_C/Matrix.o ../Lab_06_C/MatrixIO.o

OUTFILE = Lab_06_Tests

all: $(SOURCES) $(PROJOBJ) $(OBJECTS) $(OUTFILE)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS) $(PROJOBJ)
	$(CC) $(OBJECTS) $(PROJOBJ) $(LCUNIT) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)

