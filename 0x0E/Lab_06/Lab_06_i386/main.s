    .text

    .globl main
main:
    pushl %ebp
    movl %esp, %ebp
    pushl %esi
    subl $28, %esp

    # Занятый стек 40 байт:
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] old %esi
    #  -4(%ebp) [4] 
    #  -8(%ebp) [4] 
    # -12(%ebp) [4] m
    # -16(%ebp) [4] n
    # -20(%ebp) [4] pMatrix
    # -24(%ebp) [4] 8(%esp)
    # -28(%ebp) [4] 4(%esp)
    # -32(%ebp) [4] 0(%esp)

    # 4(%esp) [4] &n
    # 0(%esp) [4] &m
    leal -12(%ebp), %eax
    movl %eax, (%esp)
    leal -16(%ebp), %eax
    movl %eax, 4(%esp)
    calll ReadMN

    # 0(%esp) [4] m * n * 4
    movl -12(%ebp), %eax
    imull -16(%ebp), %eax
    imull $4, %eax
    movl %eax, (%esp)
    calll malloc
    movl %eax, -20(%ebp)

    # 8(%esp) [4] n
    # 4(%esp) [4] m
    # 0(%esp) [4] pMatrix
    movl -12(%ebp), %ecx
    movl -16(%ebp), %edx
    movl %eax, (%esp)
    movl %ecx, 4(%esp)
    movl %edx, 8(%esp)
    calll ReadMatrix

    # 0(%esp) [4] &NewLine1
    leal NewLine1, %eax
    movl %eax, (%esp)
    calll printf

    # 8(%esp) [4] n
    # 4(%esp) [4] m
    # 0(%esp) [4] pMatrix
    movl -20(%ebp), %ecx
    movl -12(%ebp), %edx
    movl -16(%ebp), %esi
    movl %ecx, (%esp)
    movl %edx, 4(%esp)
    movl %esi, 8(%esp)
    calll WriteMatrix

    # 8(%esp) [4] n
    # 4(%esp) [4] m
    # 0(%esp) [4] pMatrix
    movl -20(%ebp), %eax
    movl -12(%ebp), %ecx
    movl -16(%ebp), %edx
    movl %eax, (%esp)
    movl %ecx, 4(%esp)
    movl %edx, 8(%esp)
    calll CountDifferentLines

    # 4(%esp) [4] CountDifferentLines()
    # 0(%esp) [4] &MessageCountLinesFormat1
    leal MessageCountLinesFormat1, %ecx
    movl %ecx, (%esp)
    movl %eax, 4(%esp)
    calll printf

    # 8(%esp) [4] n
    # 4(%esp) [4] m
    # 0(%esp) [4] pMatrix
    movl -20(%ebp), %ecx
    movl -12(%ebp), %edx
    movl -16(%ebp), %esi
    movl %ecx, (%esp)
    movl %edx, 4(%esp)
    movl %esi, 8(%esp)
    calll CountDifferentRows

    # 4(%esp) [4] CountDifferentRows()
    # 0(%esp) [4] &MessageCountLinesFormat1
    leal MessageCountRowsFormat1, %ecx
    movl %ecx, (%esp)
    movl %eax, 4(%esp)
    calll printf

    # 0(%esp) [4] pMatrix
    movl -20(%ebp), %ecx
    movl %ecx, (%esp)
    calll free
    
    # return 0
    movl $0, %eax

    addl $28, %esp
    popl %esi
    popl %ebp
    retl


NewLine1:
    .asciz "\n"

MessageCountLinesFormat1:
    .asciz "Кол-во строк, все элементы которых различны: %d\n"

MessageCountRowsFormat1:
    .asciz "Кол-во столбцов, все элементы которых различны: %d\n"
