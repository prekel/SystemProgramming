.section .data

   prompt_str:
      .ascii "Enter Your Name: "
   pstr_end:
      .set STR_SIZE, pstr_end - prompt_str

   greet_str:
      .ascii "Hello "


   gstr_end:
      .set GSTR_SIZE, gstr_end - greet_str

.section .bss

// Резервирование 32 байт памяти
   .lcomm  buff, 32

// Макрос с двумя параметрами
// Реализует системный вызов для записи
   .macro write str, str_size 
      movl  $4, %eax
      movl  $1, %ebx
      movl  \str, %ecx
      movl  \str_size, %edx
      int   $0x80
   .endm


// Реализует системный вызов для чтения
   .macro read buff, buff_size
      movl  $3, %eax
      movl  $0, %ebx
      movl  \buff, %ecx
      movl  \buff_size, %edx
      int   $0x80
   .endm


.section .text

   .globl main

   main:
      write $prompt_str, $STR_SIZE
      read  $buff, $32

// Чтение возвращает длину в eax
      pushl %eax

// Вывод приветсвия
      write $greet_str, $GSTR_SIZE

      popl  %edx

// edx = длина, возвращенная чтением
   write $buff, %edx

   _exit:
      movl  $1, %eax
      movl  $0, %ebx
      ret
