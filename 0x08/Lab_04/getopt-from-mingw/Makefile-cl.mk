CC = cl.exe
AR = lib.exe
LINK = link.exe

CFLAGS = /nologo /W0 /MDd /Ob0 /Od /RTC1
LDFLAGS = /nologo
INC = /I.



SOURCES = getopt.c
OBJECTS = $(SOURCES:.c=.obj)

OUTFILE = getopt-from-mingw.lib

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) $(LDFLAGS) /OUT:$(OUTFILE) $(OBJECTS)

%.obj: %.c
	$(CC) /c $(INC) $(CFLAGS) $< /Fo$@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.obj
