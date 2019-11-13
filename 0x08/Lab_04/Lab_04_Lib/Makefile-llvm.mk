LLVMVERSION = -9
CC = clang$(LLVMVERSION)
CLANG = clang$(LLVMVERSION)
LLC = llc$(LLVMVERSION)
LLVM-AS = llvm-as$(LLVMVERSION)
AR = ar

CFLAGS = -O2 -Wall -std=gnu99
SFLAGS = -O2 -Wall 
LDFLAGS =
INC =


SOURCES = Archipelago.c RecordFile.c Meta.c ParseInt.c IOWrapper.c
LLIRS = $(SOURCES:.c=.ll)
LLBYTES = $(LLIRS:.ll=.bc)
ASMS = $(LLBYTES:.bc=.s)
OBJECTS = $(ASMS:.s=.o)

OUTFILE = libLab_04_Lib.a

all: $(SOURCES) $(LLIRS) $(LLBYTES) $(ASMS) $(OBJECTS) $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(AR) $(LDFLAGS) -r $(OUTFILE) $(OBJECTS)

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

