    .text

    .globl	main
main:
    pushl	%ebp
    movl	%esp, %ebp
    pushl	%esi
    subl	$52, %esp
    movl	$0, -8(%ebp)
    leal	-12(%ebp), %eax
    movl	%eax, (%esp)
    leal	-16(%ebp), %eax
    movl	%eax, 4(%esp)
    calll	ReadMN
    movl	-12(%ebp), %eax
    imull	-16(%ebp), %eax
    shll	$2, %eax
    movl	%eax, (%esp)
    calll	malloc
    movl	%eax, -20(%ebp)
    movl	-20(%ebp), %eax
    movl	-12(%ebp), %ecx
    movl	-16(%ebp), %edx
    movl	%eax, (%esp)
    movl	%ecx, 4(%esp)
    movl	%edx, 8(%esp)
    calll	ReadMatrix
    leal	NewLine1, %eax
    movl	%eax, (%esp)
    calll	printf
    movl	-20(%ebp), %ecx
    movl	-12(%ebp), %edx
    movl	-16(%ebp), %esi
    movl	%ecx, (%esp)
    movl	%edx, 4(%esp)
    movl	%esi, 8(%esp)
    movl	%eax, -24(%ebp)
    calll	WriteMatrix
    movl	-20(%ebp), %eax
    movl	-12(%ebp), %ecx
    movl	-16(%ebp), %edx
    movl	%eax, (%esp)
    movl	%ecx, 4(%esp)
    movl	%edx, 8(%esp)
    calll	CountDifferentLines
    leal	MessageCountLinesFormat1, %ecx
    movl	%ecx, (%esp)
    movl	%eax, 4(%esp)
    calll	printf
    movl	-20(%ebp), %ecx
    movl	-12(%ebp), %edx
    movl	-16(%ebp), %esi
    movl	%ecx, (%esp)
    movl	%edx, 4(%esp)
    movl	%esi, 8(%esp)
    movl	%eax, -28(%ebp)
    calll	CountDifferentRows
    leal	MessageCountRowsFormat1, %ecx
    movl	%ecx, (%esp)
    movl	%eax, 4(%esp)
    calll	printf
    movl	-20(%ebp), %ecx
    movl	%ecx, (%esp)
    movl	%eax, -32(%ebp)
    calll	free
    xorl	%eax, %eax
    addl	$52, %esp
    popl	%esi
    popl	%ebp
    retl


NewLine1:
    .asciz	"\n"

MessageCountLinesFormat1:
    .asciz	"Кол-во строк, все элементы которых различны: %d\n"

MessageCountRowsFormat1:
    .asciz	"Кол-во столбцов, все элементы которых различны: %d\n"
