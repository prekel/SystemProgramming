CC = gcc

CFLAGS = -O0 -g -Wall --std=gnu11
LDFLAGS = -L../Lab_04_Lib/ -lLab_04_Lib -L../getopt-from-mingw/ -lgetopt-from-mingw
INCLUDE = -I../Lab_04_Lib/ -I../getopt-from-mingw/

SOURCES = main.c Commands.c Args.c Print.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_04_Console

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) -c $(INCLUDE) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
