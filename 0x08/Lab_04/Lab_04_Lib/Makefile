CC = gcc
AR = ar


CFLAGS = -O0 -g -Wall -std=gnu99
LDFLAGS =
INC =



SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = libLab_04_Lib.a

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) $(LDFLAGS) -r $(OUTFILE) $(OBJECTS)

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
