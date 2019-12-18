AS = as 
GCC = gcc 
LLVMVERSION=-8
CLANG = clang$(LLVMVERSION) 
LLC = llc$(LLVMVERSION)
OPT = opt$(LLVMVERSION)

ASFLAGS = --32
CLANGFLAGS = -c -target i386
LDFLAGS = -m32

all : clang_O0 clang_Os gcc_O0 gcc_Os

clang_O0.ll : main.c
	$(CLANG) $(CLANGFLAGS) -S -emit-llvm -O0 $^ -o $@

clang_Os.ll : main.c
	$(CLANG) $(CLANGFLAGS) -S -emit-llvm -Os $^ -o $@

clang_O0.s : clang_O0.ll
	$(LLC) $^ -o $@

clang_Os.s : clang_Os.ll
	$(LLC) $^ -o $@


gcc_O0.s : main.c
	$(GCC) $(LDFLAGS) -S -O0 $^ -o $@

gcc_Os.s : main.c
	$(GCC) $(LDFLAGS) -S -Os $^ -o $@



clang_O0.o : clang_O0.s
	$(AS) $(ASFLAGS) $^ -o $@

clang_Os.o : clang_Os.s
	$(AS) $(ASFLAGS) $^ -o $@


gcc_O0.o : gcc_O0.s
	$(AS) $(ASFLAGS) $^ -o $@

gcc_Os.o : gcc_Os.s
	$(AS) $(ASFLAGS) $^ -o $@



clang_O0 : clang_O0.o
	$(CLANG) $(LDFLAGS) $^ -o $@

clang_Os : clang_Os.o
	$(CLANG) $(LDFLAGS) $^ -o $@

gcc_O0 : gcc_O0.o
	$(CLANG) $(LDFLAGS) $^ -o $@

gcc_Os : gcc_Os.o
	$(CLANG) $(LDFLAGS) $^ -o $@

.PHONY : clean
clean :
	rm *.o *.s *.ll clang_O0 clang_Os gcc_O0 gcc_Os
