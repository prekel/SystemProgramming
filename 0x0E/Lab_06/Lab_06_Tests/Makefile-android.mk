CC = clang


CFLAGS = -O0 -Wall -std=gnu99
LDFLAGS =
INC = -I.. -I.


SOURCES = main.c MatrixTests.c Suite.c
OBJECTS = $(SOURCES:.c=.o)

LCUNIT = -L./CUnit/android -lcunit
PROJOBJ = ../Lab_06_aarch64-gas/Matrix.o ../Lab_06_aarch64-gas/MatrixIO.o

OUTFILE = Lab_06_Tests

all: $(SOURCES) $(PROJOBJ) $(OBJECTS) $(OUTFILE)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS) $(PROJOBJ)
	$(CC) $(OBJECTS) $(PROJOBJ) $(LCUNIT) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OUTFILE) $(OBJECTS)

