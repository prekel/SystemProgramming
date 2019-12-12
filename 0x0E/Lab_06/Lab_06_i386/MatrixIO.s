	.text

	.globl	ReadMN
ReadMN:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$36, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	leal	.L.str, %edx
	movl	%edx, (%esp)
	movl	%eax, -8(%ebp)          # 4-byte Spill
	movl	%ecx, -12(%ebp)         # 4-byte Spill
	calll	printf
	movl	8(%ebp), %ecx
	movl	12(%ebp), %edx
	leal	.L.str.1, %esi
	movl	%esi, (%esp)
	movl	%ecx, 4(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, -16(%ebp)         # 4-byte Spill
	calll	__isoc99_scanf
	addl	$36, %esp
	popl	%esi
	popl	%ebp
	retl
	

	.globl	ReadMatrix
ReadMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	$0, -4(%ebp)
.LBB1_1:
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	.LBB1_8
	movl	$0, -8(%ebp)
.LBB1_3:
	movl	-8(%ebp), %eax
	cmpl	16(%ebp), %eax
	jge	.LBB1_6
	movl	-4(%ebp), %eax
	movl	-8(%ebp), %ecx
	leal	.L.str.2, %edx
	movl	%edx, (%esp)
	movl	%eax, 4(%esp)
	movl	%ecx, 8(%esp)
	calll	printf
	movl	8(%ebp), %ecx
	movl	-4(%ebp), %edx
	imull	16(%ebp), %edx
	addl	-8(%ebp), %edx
	shll	$2, %edx
	addl	%edx, %ecx
	leal	.L.str.3, %edx
	movl	%edx, (%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, -12(%ebp)
	calll	__isoc99_scanf
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	.LBB1_3
.LBB1_6:
	jmp	.LBB1_7
.LBB1_7:
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
	jmp	.LBB1_1
.LBB1_8:
	addl	$24, %esp
	popl	%ebp
	retl
	

	.globl	WriteMatrix
WriteMatrix:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$44, %esp
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	12(%ebp), %esi
	movl	16(%ebp), %edi
	leal	.L.str.4, %ebx
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	movl	%eax, -24(%ebp)
	movl	%ecx, -28(%ebp)
	movl	%edx, -32(%ebp)
	calll	printf
	movl	$0, -16(%ebp)
.LBB2_1:
	movl	-16(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	.LBB2_8
	movl	$0, -20(%ebp)
.LBB2_3:
	movl	-20(%ebp), %eax
	cmpl	16(%ebp), %eax
	jge	.LBB2_6
	movl	8(%ebp), %eax
	movl	-16(%ebp), %ecx
	imull	16(%ebp), %ecx
	addl	-20(%ebp), %ecx
	movl	(%eax,%ecx,4), %eax
	leal	.L.str.5, %ecx
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	calll	printf
	movl	-20(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -20(%ebp)
	jmp	.LBB2_3
.LBB2_6:
	leal	.L.str.6, %eax
	movl	%eax, (%esp)
	calll	printf
	movl	-16(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -16(%ebp)
	jmp	.LBB2_1
.LBB2_8:
	addl	$44, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
	

.L.str:
	.asciz	"Введите M и N (кол-во строк и столбцов, a[M][N]): "
	
.L.str.1:
	.asciz	"%d%d"
	
.L.str.2:
	.asciz	"Введите a[%d][%d]: "
	
.L.str.3:
	.asciz	"%d"
	
.L.str.4:
	.asciz	"Матрица a[%d][%d]:\n"
	
.L.str.5:
	.asciz	"%d "
	
.L.str.6:
	.asciz	"\n"
