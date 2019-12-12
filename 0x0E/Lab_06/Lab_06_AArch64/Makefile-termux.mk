AS = as
CC = clang


CFLAGS = 
LDFLAGS =
INC = 



SOURCES = main.s Matrix.s MatrixIO.s
OBJECTS = $(SOURCES:.s=.o)

OUTFILE = Lab_06_AArch64

all: $(SOURCES) $(OUTFILE)

%.o: %.s
	$(AS) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) $(OBJECTS)

