CC = aarch64-linux-gnu-gcc



CFLAGS = 
LDFLAGS = -static
INC = 



SOURCES = main.s Matrix.s MatrixIO.s
OBJECTS = $(SOURCES:.s=.o)

OUTFILE = Lab_06_AArch64

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.s
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o

