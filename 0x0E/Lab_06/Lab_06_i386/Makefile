CC = gcc
AS = as


CFLAGS = --32
LDFLAGS = -m32
INC = 



SOURCES = main.s Matrix.s 
OBJECTS = $(SOURCES:.s=.o)

OUTFILE = Lab_06_i386

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.s
	$(AS) -c $(INC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
