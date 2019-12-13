CC = "C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe"


CFLAGS = -O0 -Wall -fno-stack-protector -std=gnu99 -m32
LDFLAGS = -m32
INC = -I..



SOURCES = main.c Matrix.c MatrixIO.c
ASMS = $(SOURCES:.c=.s)
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_06_C.exe

all: $(SOURCES) $(ASMS) $(OBJECTS) $(OUTFILE) 

%.s: %.c
	$(CC) -S $(INC) $(CFLAGS) $< -o $@

%.o: %.s
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@


.PHONY: clean
clean:
	del $(OUTFILE) $(OBJECTS) $(ASMS)

