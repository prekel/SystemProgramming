AS = mips-linux-gnu-as
GCC = mips-linux-gnu-gcc 
LLVMVERSION=-8
CLANG = clang$(LLVMVERSION) 
LLC = llc$(LLVMVERSION)
OPT = opt$(LLVMVERSION)

ASFLAGS = 
CLANGFLAGS = -c -target mips
LDFLAGS = 

all : clang_O0.s clang_Os.s gcc_O0.s gcc_Os.s


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


.PHONY : clean
clean :
	rm *.o *.s *.ll
