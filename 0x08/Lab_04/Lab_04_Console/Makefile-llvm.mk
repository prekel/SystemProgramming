LLVMVERSION = -9
CC = clang$(LLVMVERSION)
CLANG = clang$(LLVMVERSION)
LLC = llc$(LLVMVERSION)
LLVM-AS = llvm-as$(LLVMVERSION)
AR = ar

CFLAGS = -O2 -Wall -std=gnu99
SFLAGS = -O2 -Wall 
LDFLAGS = -L../Lab_04_Lib/ -lLab_04_Lib
INC = -I../Lab_04_Lib/


SOURCES = main.c Commands.c Args.c Print.c
LLIRS = $(SOURCES:.c=.ll)
LLBYTES = $(LLIRS:.ll=.bc)
ASMS = $(LLBYTES:.bc=.s)
OBJECTS = $(ASMS:.s=.o)

OUTFILE = Lab_04_Console

all: $(SOURCES) $(LLIRS) $(LLBYTES) $(ASMS) $(OBJECTS) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.ll: %.c
	$(CLANG) -c $(INC) $(CFLAGS) -S -emit-llvm $< -o $@

%.bc: %.ll
	$(LLVM-AS) $<

%.s: %.ll
	$(LLC) $<

%.o: %.s
	$(CC) -c $(INC) $(SFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OUTFILE) *.o *.s *.ll *.bc
