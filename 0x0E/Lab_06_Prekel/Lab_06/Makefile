MAKE = make

.PHONY : \
Main-i386 Main-i386_clean \
Main-aarch64 Main-aarch64_clean \
Main-C Main-C_clean \
Main-C-i386 \
Main-C-aarch64 \
Main-aarch64-android \
Main-C-android \
Tests-i386 \
Tests-aarch64 \
Tests-C \
Tests-C-i386 \
Tests-C-aarch64 \
Tests-aarch64-android \
Tests-C-android \
Main_clean \
Tests_clean \
clean \
help \

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

Main-C-i386 :
	$(MAKE) -C Lab_06_C CC=gcc CFLAGS="-O0 -Wall -std=gnu99 -m32" LDFLAGS="-m32"

Main-C-aarch64 :
	$(MAKE) -C Lab_06_C CC=aarch64-linux-gnu-gcc CFLAGS="-O0 -Wall -std=gnu99" LDFLAGS="-static"

Main-aarch64-android :
	$(MAKE) -C Lab_06_aarch64-gas AS=as CC=clang LDFLAGS=
	
Main-C-android :
	$(MAKE) -C Lab_06_C CC=clang LDFLAGS=


Tests-i386 : Main-i386
	$(MAKE) -C Lab_06_Tests CC=gcc CFLAGS="-O0 -Wall -std=gnu99 -m32" LDFLAGS="-m32" LCUNIT="-L./CUnit/i386 -lcunit" PROJOBJ="../Lab_06_i386-gas/Matrix.o ../Lab_06_i386-gas/MatrixIO.o" 

Tests-aarch64 : Main-aarch64
	$(MAKE) -C Lab_06_Tests CC=aarch64-linux-gnu-gcc CFLAGS="-O0 -Wall -std=gnu99" LDFLAGS="-static" LCUNIT="-L./CUnit/aarch64 -lcunit" PROJOBJ="../Lab_06_aarch64-gas/Matrix.o ../Lab_06_aarch64-gas/MatrixIO.o"

Tests-C : Main-C
	$(MAKE) -C Lab_06_Tests

Tests-C-i386 : Main-C-i386
	$(MAKE) -C Lab_06_Tests CC=gcc CFLAGS="-O0 -Wall -std=gnu99 -m32" LDFLAGS="-m32" LCUNIT="-L./CUnit/i386 -lcunit"

Tests-C-aarch64 : Main-C-aarch64
	$(MAKE) -C Lab_06_Tests CC=aarch64-linux-gnu-gcc CFLAGS="-O0 -Wall -std=gnu99" LDFLAGS=-static LCUNIT="-L./CUnit/aarch64 -lcunit"

Tests-aarch64-android : Main-aarch64-android
	$(MAKE) -C Lab_06_Tests CC=clang CFLAGS="-O0 -Wall -std=gnu99" LDFLAGS= LCUNIT="-L./CUnit/android -lcunit" PROJOBJ="../Lab_06_aarch64-gas/Matrix.o ../Lab_06_aarch64-gas/MatrixIO.o"

Tests-C-android : Main-C-android
	$(MAKE) -C Lab_06_Tests CC=clang LCUNIT="-L./CUnit/android -lcunit" 


Main_clean : Main-i386_clean Main-aarch64_clean Main-C_clean

Tests_clean : 
	$(MAKE) -C Lab_06_Tests clean

clean : Main_clean Tests_clean


help :
	@echo \
	"Использование: make цель\n" \
	"Цели:\n" \
	" Main-i386             Главная программа, написанная на ассемблере x86_32.\n" \
	"                        Исполняемый файл ./Lab_06_i386-gas/Lab_06_i386-gas\n" \
	" Main-aarch64          Главная программа, написанная на ассемблере AArch64.\n" \
	"                        Исполняемый файл ./Lab_06_aarch64-gas/Lab_06_aarch64-gas\n" \
	" Main-C                Главная программа, написанная на C.\n" \
	"                        Исполняемый файл ./Lab_06_C/Lab_06_C\n" \
	" Main-C-i386           Главная программа, написанная на C, собираемая под x86_32.\n" \
	"                        Исполняемый файл ./Lab_06_C/Lab_06_C\n" \
	" Main-C-aarch64        Главная программа, написанная на C, собираемая под AArch64.\n" \
	"                        Исполняемый файл ./Lab_06_C/Lab_06_C\n" \
	" Main-aarch64-android  Главная программа, написанная на ассемблере AArch64. Для сборки из под Android.\n" \
	"                        Исполняемый файл ./Lab_06_aarch64-gas/Lab_06_aarch64-gas\n" \
	" Main-C-android        Главная программа, написанная на C. Для сборки из под Android.\n" \
	"                        Исполняемый файл ./Lab_06_C/Lab_06_C\n" \
	" Tests-i386            Тесты, написанные на C, проверяющие функции, написанные на ассемблере x86_32.\n" \
	"                        Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-aarch64         Тесты, написанные на C, проверяющие функции, написанные на ассемблере AArch64.\n" \
	"                        Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-C               Тесты, написанные на C, проверяющие функции, написанные на C.\n" \
	"                        Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-C-i386          Тесты, написанные на C, проверяющие функции, написанные на C. Собирается под x86_32.\n" \
	"                        Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-C-aarch64       Тесты, написанные на C, проверяющие функции, написанные на C. Собирается под AArch64.\n" \
	"                        Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-aarch64-android Тесты, написанные на C, проверяющие функции, написанные на ассемблере AArch64. Для сборки из под Android.\n" \
	"                        Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Tests-C-android       Тесты, написанные на C, проверяющие функции, написанные на C. Для сборки из под Android.\n" \
	"                        Исполняемый файл ./Lab_06_Tests/Lab_06_Tests\n" \
	" Main-i386_clean       Очищает папку Lab_06_i386-gas.\n" \
	"                        Может потребоваться перед сборкой файла ./Lab_06_i386-gas/Lab_06_i386-gas\n" \
	" Main-aarch64_clean    Очищает папку Lab_06_aarch64-gas.\n" \
	"                        Может потребоваться перед сборкой файла ./Lab_06_aarch64-gas/Lab_06_aarch64-gas\n" \
	" Main-C_clean          Очищает папку Lab_06_C.\n" \
	"                        Может потребоваться перед сборкой файла ./Lab_06_C/Lab_06_C\n" \
	" Tests_clean           Очищает паку Lab_06_Tests.\n" \
	"                        Может потребоваться перед сборкой файла ./Lab_06_Tests/Lab_06_Tests\n" \
	" clean                 Очищает всё.\n" \
	" help                  Выводит справку." \
