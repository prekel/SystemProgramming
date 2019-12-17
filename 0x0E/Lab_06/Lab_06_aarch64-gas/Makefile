AS = aarch64-linux-gnu-as
CC = aarch64-linux-gnu-gcc

CFLAGS = 
LDFLAGS = -static
INC = 



SOURCES = main.s Matrix.s MatrixIO.s
OBJECTS = $(SOURCES:.s=.o)

OUTFILE = Lab_06_aarch64-gas

all: $(SOURCES) $(OBJECTS) $(OUTFILE)

%.o: %.s
	$(AS) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(OUTFILE) $(OBJECTS)
