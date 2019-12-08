AS = as 
GCC = gcc 
LLVMVERSION=-8
CLANG = clang$(LLVMVERSION) 
LLC = llc$(LLVMVERSION)
OPT = opt$(LLVMVERSION)

all : clang_O0_clang clang_O0_as clang_O2_clang clang_O2_as gcc_O0_clang gcc_O0_as gcc_O2_clang gcc_O2_as 


clang_O0.ll : main.c
	$(CLANG) -S -emit-llvm -O0 $^ -o $@

clang_O2.ll : main.c
	$(CLANG) -S -emit-llvm -O2 $^ -o $@

clang_O0.s : clang_O0.ll
	$(LLC) $^ -o $@

clang_O2.s : clang_O2.ll
	$(LLC) $^ -o $@


gcc_O0.s : main.c
	$(GCC) -S -O0 $^ -o $@

gcc_O2.s : main.c
	$(GCC) -S -O2 $^ -o $@


clang_O0_clang.o : clang_O0.s
	$(CLANG) $^ -o $@

clang_O0_as.o : clang_O0.s
	$(AS) $^ -o $@

clang_O2_clang.o : clang_O2.s
	$(CLANG) $^ -o $@

clang_O2_as.o : clang_O2.s
	$(AS) $^ -o $@


gcc_O0_clang.o : gcc_O0.s
	$(CLANG) $^ -o $@

gcc_O0_as.o : gcc_O0.s
	$(AS) $^ -o $@

gcc_O2_clang.o : gcc_O2.s
	$(CLANG) $^ -o $@

gcc_O2_as.o : gcc_O2.s
	$(AS) $^ -o $@



clang_O0_clang : clang_O0_clang.o
	$(CLANG) $^ -o $@

clang_O0_as : clang_O0_as.o
	$(CLANG) $^ -o $@

clang_O2_clang : clang_O2_clang.o
	$(CLANG) $^ -o $@

clang_O2_as : clang_O2_as.o
	$(CLANG) $^ -o $@


gcc_O0_clang : gcc_O0_clang.o
	$(CLANG) $^ -o $@

gcc_O0_as : gcc_O0_as.o
	$(CLANG) $^ -o $@

gcc_O2_clang : gcc_O2_clang.o
	$(CLANG) $^ -o $@

gcc_O2_as : gcc_O2_as.o
	$(CLANG) $^ -o $@

.PHONY : clean
clean :
	rm *.o *.s *.ll clang_O0_clang clang_O0_as clang_O2_clang clang_O2_as gcc_O0_clang gcc_O0_as gcc_O2_clang gcc_O2_as 
