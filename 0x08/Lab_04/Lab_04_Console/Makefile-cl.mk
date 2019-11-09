CC = cl
LINK = link.exe
AR = lib.exe

CFLAGS = /nologo /W3 /MDd /Ob0 /Od /RTC1
INC = -I../Lab_04_Lib/ -I../getopt-from-mingw/

LIBS = ../Lab_04_Lib/Lab_04_Lib.lib ../getopt-from-mingw/getopt-from-mingw.lib

SOURCES = main.c Commands.c Args.c Print.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_04_Console.exe

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(LINK) /OUT:$(OUTFILE) $(OBJECTS) $(LIBS)

.c.o:
	$(CC) /c $(INC) $(CFLAGS) $< /Fo$@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.o
