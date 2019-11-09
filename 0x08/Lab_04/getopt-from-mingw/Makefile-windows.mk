CC = cl
AR = lib

CFLAGS = -O0 -g -Wall --std=gnu11
LDFLAGS=

SOURCES = getopt.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = getopt-from-mingw.lib

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
