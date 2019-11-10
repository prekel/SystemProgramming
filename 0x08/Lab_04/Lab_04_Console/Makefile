CC = gcc



CFLAGS = -O0 -g -Wall
LDFLAGS = -L../Lab_04_Lib/ -lLab_04_Lib
INC = -I../Lab_04_Lib/



SOURCES = main.c Commands.c Args.c Print.c
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = Lab_04_Console

all: $(SOURCES) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o
