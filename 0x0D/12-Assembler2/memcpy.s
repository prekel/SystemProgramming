.data
printf_format:
        .string "%s\n"

str_in:
        .string "abc123()!@!777"
        .set str_in_length, .-str_in

.bss
str_out:
        .space str_in_length

.text

/* void* my_memcpy(void *dest, const void *src, size_t n); */

my_memcpy:
        pushl %ebp
        movl  %esp, %ebp

        pushl %esi
        pushl %edi

        movl  8(%ebp), %edi     /* цепочка-назначение                */
        movl  12(%ebp), %esi    /* цепочка-источник                  */
        movl  16(%ebp), %ecx    /* длина                             */

        rep movsb

        movl  8(%ebp), %eax     /* вернуть dest                      */

        popl  %edi
        popl  %esi

        movl  %ebp, %esp
        popl  %ebp
        ret

.globl main
main:
        pushl %ebp
        movl  %esp, %ebp

        pushl $str_in_length
        pushl $str_in
        pushl $str_out
        call  my_memcpy

        pushl $str_out
        pushl $printf_format
        call  printf

        movl  $0, %eax

        movl  %ebp, %esp
        popl  %ebp
        ret
