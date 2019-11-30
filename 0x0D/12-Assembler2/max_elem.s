.data
printf_format:
        .string "%d\n"
 
array:
        .long 100, 15, 148, 12, 151, 3, 72
array_end:
 
.text
.globl main
main:
        movl  $0, %eax          /* � %eax ����� ��������� ���������;
                                   � ������ ���������� �������� - 0  */
        movl  $array, %ebx      /* � %ebx ��������� ����� �������� 
                                   �������� �������                  */
 
loop_start:                     /* ������ �����                      */
        cmpl  %eax, (%ebx)      /* �������� ������� ������� ������� � 
                                   ������� ���������� ��������� �� %eax
                                                                     */
        jbe   less              /* ���� ������� ������� ������� ������ 
                                   ��� ����� �����������, ���������� 
                                   ��������� ���                     */
        movl  (%ebx), %eax      /* � ��� ���� ������� ������� 
                                   ����������� ����������, ������, ��� 
                                   �������� � ���� ����� ��������    */
less:
        addl  $4, %ebx          /* ��������� %ebx �� ������ ������ 
                                   �������� �������, 4 �����         */
        cmpl  $array_end, %ebx  /* �������� ����� �������� �������� � 
                                   ����� ����� �������               */
        je    loop_end          /* ���� ��� �����, ����� �� �����    */
        jmp   loop_start        /* ����� ��������� ���� �����        */
loop_end:
 
/*
 * ��������� ��� ������� ����� �� %eax �� ����� � ��������� ���������
 */
        pushl %eax
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl  $0, %eax
        ret
