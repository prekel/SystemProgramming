AS = aarch64-linux-gnu-as
GCC = aarch64-linux-gnu-gcc 
LLVMVERSION=-8
CLANG = clang$(LLVMVERSION) 
LLC = llc$(LLVMVERSION)
OPT = opt$(LLVMVERSION)

ASFLAGS = 
CLANGFLAGS = -c -target aarch64
LDFLAGS = -static

all : clang_O0 clang_O2 gcc_O0 gcc_O2

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



clang_O0.o : clang_O0.s
	$(AS) $(ASFLAGS) $^ -o $@

clang_O2.o : clang_O2.s
	$(AS) $(ASFLAGS) $^ -o $@


gcc_O0.o : gcc_O0.s
	$(AS) $(ASFLAGS) $^ -o $@

gcc_O2.o : gcc_O2.s
	$(AS) $(ASFLAGS) $^ -o $@



clang_O0 : clang_O0.o
	$(GCC) $(LDFLAGS) $^ -o $@

clang_O2 : clang_O2.o
	$(GCC) $(LDFLAGS) $^ -o $@

gcc_O0 : gcc_O0.o
	$(GCC) $(LDFLAGS) $^ -o $@

gcc_O2 : gcc_O2.o
	$(GCC) $(LDFLAGS) $^ -o $@

.PHONY : clean
clean :
	rm *.o *.s *.ll clang_O0 clang_O2 gcc_O0 gcc_O2
