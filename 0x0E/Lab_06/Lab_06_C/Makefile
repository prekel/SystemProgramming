CC = gcc



CFLAGS = -O0 -g -Wall -std=gnu99
LDFLAGS = 
INC = -I..



SOURCES = main.c Matrix.c MatrixIO.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_06_C

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
