AS = mips-linux-gnu-as
GCC = mips-linux-gnu-gcc 
LLVMVERSION=-8
CLANG = clang$(LLVMVERSION) 
LLC = llc$(LLVMVERSION)
OPT = opt$(LLVMVERSION)

ASFLAGS = 
CLANGFLAGS = -c -target mips
LDFLAGS = 

all : clang_O0.s clang_O2.s gcc_O0.s gcc_O2.s


clang_O0.ll : main.c
	$(CLANG) $(CLANGFLAGS) -S -emit-llvm -O0 $^ -o $@

clang_O2.ll : main.c
	$(CLANG) $(CLANGFLAGS) -S -emit-llvm -O2 $^ -o $@

clang_O0.s : clang_O0.ll
	$(LLC) $^ -o $@

clang_O2.s : clang_O2.ll
	$(LLC) $^ -o $@


gcc_O0.s : main.c
	$(GCC) $(LDFLAGS) -S -O0 $^ -o $@

gcc_O2.s : main.c
	$(GCC) $(LDFLAGS) -S -O2 $^ -o $@


.PHONY : clean
clean :
	rm *.o *.s *.ll
