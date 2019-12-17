MAKE = make

.PHONY : \
Main-i386 Main-i386_run Main-i386_clean \
Main-aarch64 Main-aarch64_run Main-aarch64_clean \
Main-C Main-C_run Main-C_clean \
Main-mips_run \
Tests-i386 Tests-i386_run Tests-i386_clean \
Tests-aarch64 Tests-aarch64_run Tests-aarch64_clean\
Tests-C Tests-C_run Tests-C-clean \
cleanall help \

all : help

Main-i386 :
	$(MAKE) -C Lab_06_i386-gas
Main-i386_run : Main-i386
	./Lab_06_i386-gas/Lab_06_i386-gas
Main-i386_clean :
	$(MAKE) -C Lab_06_i386-gas clean

Main-aarch64 :
	$(MAKE) -C Lab_06_aarch64-gas
Main-aarch64_run : Main-aarch64
	./Lab_06_aarch64-gas/Lab_06_aarch64-gas
Main-aarch64_clean :
	$(MAKE) -C Lab_06_aarch64-gas clean

Main-C :
	$(MAKE) -C Lab_06_C
Main-C_run : Main-C
	./Lab_06_C/Lab_06_C
Main-C_clean :
	$(MAKE) -C Lab_06_C clean

Main-mips_run :
	spim -f ./Lab_06_mips-spim/Lab_06_mips-spim.s

Tests-i386 : Main-i386
	$(MAKE) -C Lab_06_Tests -f Makefile-i386.mk
Tests-i386_run : Tests-i386
	./Lab_06_Tests/Lab_06_Tests
Tests-i386_clean : Main-i386_clean
	$(MAKE) -C Lab_06_Tests -f Makefile-i386.mk clean

Tests-aarch64 : Main-aarch64
	$(MAKE) -C Lab_06_Tests -f Makefile-aarch64.mk
Tests-aarch64_run : Tests-aarch64
	./Lab_06_Tests/Lab_06_Tests
Tests-aarch64_clean : Main-aarch64_clean
	$(MAKE) -C Lab_06_Tests -f Makefile-aarch64.mk clean

Tests-C : Main-C
	$(MAKE) -C Lab_06_Tests
Tests-C_run : Tests-C
	./Lab_06_Tests/Lab_06_Tests
Tests-C_clean : Main-C_clean
	$(MAKE) -C Lab_06_Tests clean

cleanall : Main-i386_clean Main-aarch64_clean Main-C_clean Tests-aarch64_clean Tests-C_clean

help :
	@echo \
	"Использование: make цель[_clean]\n" \
	"Цели:\n" \
	" Main-i386     Главная программа, написанная на ассемблере x86_32.\n" \
	"                Исполняемый файл ./Lab_06_i386-gas/Lab_06_i386-gas\n" \
	" Main-aarch64  Главная программа, написанная на ассемблере AArch64.\n" \
	"                Исполняемый файл ./Lab_06_aarch64-gas/Lab_06_aarch64-gas\n" \
	" Main-C        Главная программа, написанная на C.\n" \
	"                Исполняемый файл ./Lab_06_C/Lab_06_C\n" \
	" Tests-i386    Тесты, написанные на C, проверяющие функции, написанные на ассемблере x86_32.\n" \
	"                Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-aarch64 Тесты, написанные на C, проверяющие функции, написанные на ассемблере AArch64.\n" \
	"                Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-C       Тесты, написанные на C, проверяющие функции, написанные на C.\n" \
	"                Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" цель_clean    Очищает цель, в случае с тестами очищает и тесты, и главную программу.\n" \
	" cleanall      Очищает всё.\n" \
	" help          Выводит справку." \
