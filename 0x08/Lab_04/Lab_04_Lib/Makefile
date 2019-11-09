CC = gcc
AR = ar

CFLAGS= -O0 -g -Wall --std=gnu11
LDFLAGS=

SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = libLab_04_Lib.a

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) -r $(OUTFILE) $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
