MAKE = make

.PHONY : \
Main-i386 Main-i386_clean \
Main-aarch64 Main-aarch64_clean \
Main-C Main-C_clean \
Main-All Main-All_clean \
Tests-i386 Tests-i386_clean \
Tests-aarch64 Tests-aarch64_clean\
Tests-C Tests-C-clean \
Tests_clean \
cleanall help \

all : help

Main-i386 :
	$(MAKE) -C Lab_06_i386-gas
Main-i386_clean :
	$(MAKE) -C Lab_06_i386-gas clean

Main-aarch64 :
	$(MAKE) -C Lab_06_aarch64-gas
Main-aarch64_clean :
	$(MAKE) -C Lab_06_aarch64-gas clean

Main-C :
	$(MAKE) -C Lab_06_C
Main-C_clean :
	$(MAKE) -C Lab_06_C clean

Main-All : Main-i386 Main-aarch64 Main-C
Main-All_clean : Main-i386_clean Main-aarch64_clean Main-C_clean

Tests-i386 : Main-i386
	$(MAKE) -C Lab_06_Tests -f Makefile-i386.mk
Tests-i386_clean : Tests_clean

Tests-aarch64 : Main-aarch64
	$(MAKE) -C Lab_06_Tests -f Makefile-aarch64.mk
Tests-aarch64_clean : Tests_clean

Tests-C : Main-C
	$(MAKE) -C Lab_06_Tests
Tests-C_clean : Tests_clean

Tests_clean : 
	$(MAKE) -C Lab_06_Tests clean

cleanall : Main-All_clean Tests_clean

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
	" Main-All      Главная программа (объеденяет 3 цели выше).\n" \
	" Tests-i386    Тесты, написанные на C, проверяющие функции, написанные на ассемблере x86_32.\n" \
	"                Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-aarch64 Тесты, написанные на C, проверяющие функции, написанные на ассемблере AArch64.\n" \
	"                Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-C       Тесты, написанные на C, проверяющие функции, написанные на C.\n" \
	"                Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" цель_clean    Очищает цель.\n" \
	" Tests_clean   Очищает тесты. Необходимо перед сборкой тестов для другой платформы.\n" \
	" cleanall      Очищает всё.\n" \
	" help          Выводит справку." \

