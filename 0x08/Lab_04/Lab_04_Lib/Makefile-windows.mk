CC = cl
AR = lib

CFLAGS= /O0 /Wall
LDFLAGS=

SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
OBJECTS = $(SOURCES:.c=.obj)

OUTFILE = Lab_04_Lib.lib

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) /OUT $(OUTFILE) $(OBJECTS)

.c.obj:
	$(CC) /c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.obj
