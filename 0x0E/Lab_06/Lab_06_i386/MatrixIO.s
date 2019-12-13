    .text

    .globl ReadMN
ReadMN:
    pushl   %ebp
    movl %esp, %ebp

    # Занятый стек 16 байт:
    #  12(%ebp) [4] pN
    #   8(%ebp) [4] pM
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] 

    # Занятый стек 16 байт перед вызовом printf:
    #  12(%ebp) [4] pN
    #   8(%ebp) [4] pM
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] 0(%esp) &InputMNMessage1

    leal InputMNMessage1, %edx
    pushl %edx
    calll printf
    addl $4, %esp

    # Занятый стек 24 байт перед вызовом scanf:
    #  12(%ebp) [4] pN
    #   8(%ebp) [4] pM
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] 8(%esp) 12(%ebp)
    #  -4(%ebp) [4] 4(%esp) 8(%ebp)
    #  -8(%ebp) [4] 0(%esp) &InputMNFormat1

    pushl 12(%ebp)
    pushl 8(%ebp)
    leal InputMNFormat1, %edx
    pushl %edx
    calll scanf
    addl $12, %esp

    popl %ebp
    retl


    .globl ReadMatrix
ReadMatrix:
    pushl %ebp
    movl %esp, %ebp
    subl $24, %esp

    movl 16(%ebp), %eax
    movl 12(%ebp), %ecx
    movl 8(%ebp), %edx
    movl $0, -4(%ebp)
.LBB1_1:
    movl -4(%ebp), %eax
    cmpl 12(%ebp), %eax
    jge .LBB1_8
    movl $0, -8(%ebp)
.LBB1_3:
    movl -8(%ebp), %eax
    cmpl 16(%ebp), %eax
    jge .LBB1_6
    movl -4(%ebp), %eax
    movl -8(%ebp), %ecx
    leal InputMessageFormat1, %edx
    movl %edx, (%esp)
    movl %eax, 4(%esp)
    movl %ecx, 8(%esp)
    calll printf
    movl 8(%ebp), %ecx
    movl -4(%ebp), %edx
    imull 16(%ebp), %edx
    addl -8(%ebp), %edx
    shll $2, %edx
    addl %edx, %ecx
    leal InputFormat1, %edx
    movl %edx, (%esp)
    movl %ecx, 4(%esp)
    movl %eax, -12(%ebp)
    calll scanf
    movl -8(%ebp), %eax
    addl $1, %eax
    movl %eax, -8(%ebp)
    jmp .LBB1_3
.LBB1_6:
    jmp .LBB1_7
.LBB1_7:
    movl -4(%ebp), %eax
    addl $1, %eax
    movl %eax, -4(%ebp)
    jmp .LBB1_1

.LBB1_8:

    addl $24, %esp
    popl %ebp
    retl


    .globl WriteMatrix
WriteMatrix:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    pushl %edi
    pushl %esi
    subl $20, %esp

    # Занятый стек 40 байт:
    #  16(%ebp) [4] n
    #  12(%ebp) [4] m
    #   8(%ebp) [4] pMatrix
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] old %ebx
    #  -4(%ebp) [4] old %edi
    #  -8(%ebp) [4] old %esi
    # -12(%ebp) [4] 
    # -16(%ebp) [4] i
    # -20(%ebp) [4] j
    # -24(%ebp) [4] 4(%esp)
    # -28(%ebp) [4] 0(%esp)

    leal OutputFormatMatrix1, %ebx
    push 16(%ebp)
    push 12(%ebp)
    push %ebx
    calll printf
    addl $16, %esp

    # for (-16(%ebp) <- 0; -16(%ebp) < 12(%ebp); -16(%ebp)++)
    Loop1_Start:
        movl $0, -16(%ebp)
        jmp Loop1_Check
        Loop1_Body:
            # for (-20(%ebp) <- 0; -20(%ebp) < 16(%ebp); -20(%ebp)++)
            Loop2_Start:
                movl $0, -20(%ebp)
                jmp Loop2_Check
                Loop2_Body:
                    movl 8(%ebp), %eax
                    movl -16(%ebp), %ecx
                    imull 16(%ebp), %ecx
                    addl -20(%ebp), %ecx
                    movl (%eax,%ecx,4), %eax
                    leal OutputFormat1, %ecx
                    movl %ecx, (%esp)
                    movl %eax, 4(%esp)
                    calll printf
                    movl -20(%ebp), %eax
                    addl $1, %eax
                    movl %eax, -20(%ebp)
                Loop2_Check:
                    movl -20(%ebp), %eax
                    cmpl 16(%ebp), %eax
                    jl Loop2_Body
            leal NewLine, %eax
            movl %eax, (%esp)
            calll printf
            movl -16(%ebp), %eax
            addl $1, %eax
            movl %eax, -16(%ebp)
        Loop1_Check:
            movl -16(%ebp), %eax
            cmpl 12(%ebp), %eax
            jl Loop1_Body
    
    addl $16, %esp
    popl %esi
    popl %edi
    popl %ebx
    popl %ebp
    retl


InputMNMessage1:
    .asciz "Введите M и N (кол-во строк и столбцов, a[M][N]): "

InputMNFormat1:
    .asciz "%d%d"

InputMessageFormat1:
    .asciz "Введите a[%d][%d]: "

InputFormat1:
    .asciz "%d"

OutputFormatMatrix1:
    .asciz "Матрица a[%d][%d]:\n"

OutputFormat1:
    .asciz "%d "

NewLine:
    .asciz "\n"
