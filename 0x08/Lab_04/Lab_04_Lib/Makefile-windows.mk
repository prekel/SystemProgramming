CC = cl
AR = lib

CFLAGS= /Od /Wall
LDFLAGS=

SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
OBJECTS = $(SOURCES:.c=.obj)

OUTFILE = Lab_04_Lib.lib

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) /OUT $(OUTFILE) $(OBJECTS)

.c.obj:
	$(CC) /c $(CFLAGS) $< $@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.obj
