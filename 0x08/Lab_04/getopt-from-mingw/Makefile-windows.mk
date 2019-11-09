CC = gcc
AR = ar

CFLAGS= -O0 -g -Wall --std=gnu11
LDFLAGS=

SOURCES = getopt.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = libgetopt-from-mingw.a

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) -r $(OUTFILE) $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
