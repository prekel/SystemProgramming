CC = gcc
AS = as


CFLAGS = --32
LDFLAGS = -m32
INC = 



SOURCES = main.s Matrix.s MatrixIO.s 
OBJECTS = $(SOURCES:.s=.o)

OUTFILE = Lab_06_i386

all: $(SOURCES) $(OBJECTS) $(OUTFILE)

%.o: %.s
	$(AS) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)

