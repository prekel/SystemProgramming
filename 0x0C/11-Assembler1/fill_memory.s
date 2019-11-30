.data
printf_format:   /* ��������� ������ ��� ������ ������������ ��������� ������� */
        .string "%s\n" 

.bss
array:  .space 80 /* �������� ������ ��� ���������� */
 
.text
.globl main
main:

        movl $array, %edi
        movl $80, %ecx
        movb $0x41, %al
        call fill_memory
/*
 * ��������� ��� ������� ����� � %eax �� ����� � ��������� ���������
 */
        pushl $array
        pushl $printf_format
        call  printf
        addl  $8, %esp
 
        movl $0, %eax
        ret

/* ������������ fill memory
 * (edi = �����, ecx = ������, al = ����-�����������)
 */
fill_memory:
        jecxz fm_q
fm_lp:
        movb %al, (%edi)
        incl %edi
        loop fm_lp

fm_q:   ret
