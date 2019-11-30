.data
printf_format:
        .string "%d %d\n"
 
val1:
        .long 100
val2:
        .long 200

array:
        .rept 80
        .byte 0
        .endr
endarray:
 
.text
.globl main
main:
        pushl val1
        pushl val2
        pushl $printf_format
        call  printf
        addl  $12, %esp
        
        movl val1, %eax
        xchg %eax, val2
        movl %eax, val1
 
        pushl val1
        pushl val2
        pushl $printf_format
        call  printf
        addl  $12, %esp
        movl  $0, %eax
        ret
