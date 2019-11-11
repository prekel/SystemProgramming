CC = gcc



CFLAGS = -O0 -g -Wall -std=gnu99
LDFLAGS = -L../Lab_04_Lib/ -lLab_04_Lib
INC = -I../Lab_04_Lib/



SOURCES = main.c Commands.c Args.c Print.c
OBJECTS = $(SOURCES:.c=.obj)

OUTFILE = Lab_04_Console.exe

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.obj: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	del $(OUTFILE)
	del *.obj
