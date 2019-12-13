CC = gcc


CFLAGS = -O0 -Wall -fno-stack-protector -std=gnu99
LDFLAGS = 
INC = -I..



SOURCES = main.c Matrix.c MatrixIO.c
ASMS = $(SOURCES:.c=.s)
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_06_C

all: $(SOURCES) $(ASMS) $(OBJECTS) $(OUTFILE) 

%.s: %.c
	$(CC) -S $(INC) $(CFLAGS) $< -o $@

%.o: %.s
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@


.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS) $(ASMS)

