.data
printf_format:
        .string "%d\n"
 
.text
.globl main
main:
        movl  $0, %eax          /* � %eax ����� ���������, ������� � 
                                   ������ ��� ����� ��������         */
        movl  $100, %ecx         /* 10 ����� �����                    */
 
sum:
        addl  %ecx, %eax        /* %eax = %eax + %ecx                */
        loop  sum
 
        /* %eax = 5050, %ecx = 0 */
 
/*
 * ��������� ��� ������� ����� � %eax �� ����� � ��������� ���������
 */
        pushl %eax
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl  $0, %eax
        ret
