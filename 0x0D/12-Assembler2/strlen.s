.data
printf_format:
        .string "%u\n"

str_in:
        .string "abc123()!@!777"

.text

/* size_t my_strlen(const char* s); */

my_strlen:
        pushl %ebp
        movl  %esp, %ebp

        pushl %edi

        movl  8(%ebp), %edi             /* цепочка */

        movl  $0xffffffff, %ecx
        xorl  %eax, %eax                /* %eax = 0 */

        repne scasb

        notl  %ecx
        decl  %ecx

        movl  %ecx, %eax

        popl  %edi

        movl  %ebp, %esp
        popl  %ebp
        ret

.globl main
main:
        pushl %ebp
        movl  %esp, %ebp

        pushl $str_in
        call  my_strlen

        pushl %eax
        pushl $printf_format
        call  printf

        movl  $0, %eax

        movl  %ebp, %esp
        popl  %ebp
        ret
