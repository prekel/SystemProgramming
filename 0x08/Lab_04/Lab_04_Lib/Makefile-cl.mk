CC = cl.exe
LINK = link.exe
AR = lib.exe

CFLAGS = /nologo /W0 /MDd /Ob0 /Od /RTC1
LDFLAGS = /nologo
INC = /I.



SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_04_Lib.lib

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) $(LDFLAGS) /OUT:$(OUTFILE) $(OBJECTS)

.c.o:
	$(CC) /c $(INC) $(CFLAGS) $< /Fo$@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.o
