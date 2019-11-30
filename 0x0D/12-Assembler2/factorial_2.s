.data
printf_format:
        .string "%d\n"
 
.text
/* int factorial(int) */
factorial:
        movl  4(%esp), %ecx
 
        cmpl  $0, %ecx
        jne   not_zero
 
        movl  $1, %eax
        ret
 
not_zero:
 
        movl  $1, %eax
loop_start:
        mull  %ecx
        loop  loop_start
 
        ret
 
.globl main
main:
        pushl %ebp
        movl  %esp, %ebp
 
        pushl $7
        call  factorial
 
        pushl %eax
        pushl $printf_format
        call  printf
 
        /* ���� ����� �� �����������, ��� ����� �������
           �� ����� ���������� ������� */
 
        movl  $0, %eax                  /* ��������� ��������� */
 
        movl  %ebp, %esp
        popl  %ebp
        ret
