CC = gcc


CFLAGS = -O0 -Wall -std=gnu99
LDFLAGS = 
INC = -I..



SOURCES = main.c Matrix.c MatrixIO.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_06_C

all: $(SOURCES) $(OBJECTS) $(OUTFILE) 

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OUTFILE) $(OBJECTS) 
