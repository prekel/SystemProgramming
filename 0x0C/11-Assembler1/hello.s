.data                         /* ��������� ��������� � ������� ������
                                                                    */
 
hello_str:                    /* ���� ������                        */
        .string "Hello, goodbye and farewell!\n"
 
                              /* ����� ������                       */
        .set hello_str_length, . - hello_str - 1
 
.text                         /* ��������� ��������� � ������� ���� */
 
.globl  main                  /* main - ���������� ������, �������
                                 �� ��������� �������� �����        */
.type   main, @function       /* main - ������� (� �� ������)       */
 
 
main:
        movl    $4, %eax      /* ��������� ����� ���������� ������
                                 write = 4 � ������� %eax           */
 
        movl    $1, %ebx      /* ������ �������� - � ������� %ebx;
                                 ����� ��������� ����������� 
                                 stdout - 1                         */
 
        movl    $hello_str, %ecx  /* ������ �������� - � ������� %ecx;
                                     ��������� �� ������            */
 
        movl    $hello_str_length, %edx /* ������ �������� - � �������
                                           %edx; ����� ������       */
 
        int     $0x80         /* ������� ���������� 0x80            */
 
        movl    $1, %eax      /* ����� ���������� ������ exit - 1   */
        movl    $0, %ebx      /* �������� 0 ��� �������� ���������  */
        int     $0x80         /* ������� exit(0)                    */
 
        .size   main, . - main    /* ������ ������� main            */