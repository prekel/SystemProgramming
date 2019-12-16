MAKE = make

.PHONY : \
Main-i386 Main-i386_clean \
Main-aarch64 Main-aarch64_clean \
Main-C Main-C_clean \
Tests-i386 Tests-i386_clean \
Tests-aarch64 Tests-aarch64_clean\
Tests-C Tests-C-clean \
cleanall help \

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

Tests-i386 :
	$(MAKE) -C Lab_06_i386-gas
	$(MAKE) -C Lab_06_Tests -f Makefile-i386.mk
Tests-i386_clean :
	$(MAKE) -C Lab_06_Tests -f Makefile-i386.mk clean

Tests-aarch64 :
	$(MAKE) -C Lab_06_aarch64-gas
	$(MAKE) -C Lab_06_Tests -f Makefile-aarch64.mk
Tests-aarch64_clean :
	$(MAKE) -C Lab_06_Tests -f Makefile-aarch64.mk clean

Tests-C :
	$(MAKE) -C Lab_06_C
	$(MAKE) -C Lab_06_Tests
Tests-C_clean :
	$(MAKE) -C Lab_06_Tests clean

cleanall : Main-i386_clean Main-aarch64_clean Main-C_clean Tests-aarch64_clean Tests-C_clean


help :
	@echo "Использование: make цель[_clean]\n" \
	"Цели:\n" \
	" Main-i386 главная программа, написанная на ассемблере x86_32.\n" \
	"     Исполняемый файл ./Lab_06_i386-gas/Lab_06_i386-gas\n" \
	" Main-aarch64 главная программа, написанная на ассемблере AArch64.\n" \
	"     Исполняемый файл ./Lab_06_aarch64-gas/Lab_06_aarch64-gas\n" \
	" Main-C главная программа, написанная на C.\n" \
	"     Исполняемый файл ./Lab_06_C/Lab_06_C\n" \
	" Tests-i386 тесты, написанные на C, проверяющие функции, написанные на ассемблере x86_32.\n" \
	"     Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-aarch64 тесты, написанные на C, проверяющие функции, написанные на ассемблере AArch64.\n" \
	"     Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-C тесты, написанные на C, проверяющие функции, написанные на C.\n" \
	"     Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" cleanall очищает всё.\n" \
	" help выводит справку." \
