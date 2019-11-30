.data
printf_format:
        .string "%d\n"
 
.text
/* int factorial(int) */
factorial:
        pushl %ebp
        movl  %esp, %ebp
 
        /* ������� �������� � %eax */
        movl  8(%ebp), %eax
 
        /* ��������� 0 ����� 1 */
        cmpl  $0, %eax
        jne   not_zero
 
        movl  $1, %eax
        jmp   return
not_zero:
 
        /* ��������� 4 ������ ��������� ���������
           %eax = factorial(%eax - 1) */
 
        decl  %eax
        pushl %eax
        call  factorial
        addl  $4, %esp
 
        /* ������� � %ebx �������� � ��������� %eax = %eax * %ebx */
 
        movl  8(%ebp), %ebx
        mull  %ebx
 
        /* ��������� � ���� %edx:%eax, �� ������� 32 ���� ����� 
           ���������, ��� ��� ��� �� ���������� � int */
 
return:
        movl  %ebp, %esp
        popl  %ebp
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
