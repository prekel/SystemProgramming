.data
printf_format:
        .string "%d\n"
 
array:
        .long 100, 15, 148, 12, 151, 3, 72
array_end:
 
array_size:
        .long (array_end - array)/4  /* ���������� ��������� ������� */
 
.text
.globl main
main:
        movl  $0, %eax          /* � %eax ����� ��������� ���������;
                                   � ������ ���������� �������� - 0  */
        movl  $0, %ecx          /* ������ �������� � �������� �������� 
                                                                     */
 
loop_start:                     /* ������ �����                      */
        cmpl  %eax, array(,%ecx,4)  /* �������� ������� ������� 
                                   ������� � ������� ���������� 
                                   ��������� �� %eax                 */
        jbe   less              /* ���� ������� ������� ������� ������ 
                                   ��� ����� �����������, ���������� 
                                   ��������� ���                     */
        movl  array(,%ecx,4), %eax  /* � ��� ���� ������� ������� 
                                   ����������� ����������, ������, ��� 
                                   �������� � ���� ����� ��������    */
less:
        incl  %ecx              /* ��������� �� 1 ����� �������� 
                                   ��������                          */
        cmpl  array_size, %ecx  /* �������� ����� �������� �������� � 
                                   ����� ������ ���������            */
        je    loop_end          /* ���� ��� �����, ����� �� �����    */
        jmp   loop_start        /* ����� ��������� ���� �����        */
loop_end:

/*
 * ��������� ��� ������� ����� � %eax �� ����� � ��������� ���������
 */
        pushl %eax
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl $0, %eax
        ret