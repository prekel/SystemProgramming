CC = gcc
AR = ar


CFLAGS = -O0 -g -Wall
LDFLAGS =
INC =



SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
OBJECTS = $(SOURCES:.c=.obj)

OUTFILE = libLab_04_Lib.a

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) $(LDFLAGS) -r $(OUTFILE) $(OBJECTS)

%.obj: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.obj
