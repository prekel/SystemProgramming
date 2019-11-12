LLVMVERSION = -9
CC = clang$(LLVMVERSION)
CLANG = clang$(LLVMVERSION)
LLC = llc$(LLVMVERSION)
LLVM-AS = llvm-as$(LLVMVERSION)
LLVM-DIS = llvm-dis$(LLVMVERSION)
OPT = opt$(LLVMVERSION)
AR = ar

CFLAGS = -O0 -Wall -std=gnu99
SFLAGS = -O2 -Wall 
LDFLAGS = -L../Lab_04_Lib/ -lLab_04_Lib
OPTFLAGS = -dot-callgraph -dot-cfg -dot-dom -dot-postdom
INC = -I../Lab_04_Lib/


SOURCES = main.c Commands.c Args.c Print.c

LLBYTES = $(SOURCES:.c=.bc)
LLBYTESOPT = $(LLBYTES:.bc=.optbc)
LLIRS = $(LLBYTES:.optbc=.ll)
ASMS = $(LLBYTESOPT:.optbc=.s)
OBJECTS = $(ASMS:.s=.o)

DOTS = $(wildcard *.dot) $(wildcard .*.dot) 
PNGS = $(DOTS:.dot=.png)

OUTFILE = Lab_04_Console


all: $(SOURCES) $(LLIRS) $(LLBYTES) $(LLBYTESOPT) $(ASMS) $(OBJECTS) $(OUTFILE) $(PNGS)

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.bc: %.c
	$(CLANG) -c $(INC) $(CFLAGS) -emit-llvm $< -o $@

%.optbc: %.bc
	$(OPT) $(OPTFLAGS) $< -o $@; mv callgraph.dot $(patsubst %.optbc,%.dot,callgraph.$@);

%.ll: %.optbc
	$(LLVM-DIS) $<

%.s: %.optbc
	$(LLC) $< -o $@

%.o: %.s
	$(CC) -c $(INC) $(SFLAGS) $< -o $@

%.png: %.dot
	dot -Tpng $< > $@

.PHONY: clean 
clean:
	rm $(OUTFILE) *.o *.s *.ll *.optbc *.bc .*.dot

