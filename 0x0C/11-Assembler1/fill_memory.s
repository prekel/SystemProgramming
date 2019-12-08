.data
printf_format:   /* форматная строка для вывода заполненного байтового массива */
        .string "%s\n" 

.bss
array:  .space 80 /* Байтовый массив для заполнения */
 
.text
.globl main
main:

        movl $array, %edi
        movl $80, %ecx
        movb $0x41, %al
        call fill_memory
/*
 * следующий код выводит число в %eax на экран и завершает программу
 */
        pushl $array
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl $0, %eax
        ret

/* Подпрограмма fill memory
 * (edi = адрес, ecx = размер, al = байт-заполнитель)
 */
fill_memory:
        jecxz fm_q
fm_lp:
        movb %al, (%edi)
        incl %edi
        loop fm_lp

fm_q:   ret
