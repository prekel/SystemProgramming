CC = cl.exe
LINK = link.exe
AR = lib.exe

CFLAGS= /Od /Wall
LDFLAGS=

SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_04_Lib.lib

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) /OUT: $(OUTFILE) $(OBJECTS)

.c.o:
	$(CC) /c $(CFLAGS) $< /Fo$@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.o
