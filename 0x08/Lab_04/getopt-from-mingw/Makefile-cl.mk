CC = cl.exe
LINK = link.exe
AR = lib.exe

CFLAGS= /nologo /W3 /MDd /Ob0 /Od /RTC1
INC = /I.

SOURCES = getopt.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = getopt-from-mingw.lib

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) /OUT:$(OUTFILE) $(OBJECTS)

.c.o:
	$(CC) /c $(INC) $(CFLAGS) $< /Fo$@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.o
