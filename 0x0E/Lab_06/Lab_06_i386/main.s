	.text
	.file	"main.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
# %bb.0:
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
	leal	.L.str, %eax
	movl	%eax, (%esp)
	calll	printf
	movl	-20(%ebp), %ecx
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %esi
	movl	%ecx, (%esp)
	movl	%edx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	%eax, -24(%ebp)         # 4-byte Spill
	calll	WriteMatrix
	movl	-20(%ebp), %eax
	movl	-12(%ebp), %ecx
	movl	-16(%ebp), %edx
	movl	%eax, (%esp)
	movl	%ecx, 4(%esp)
	movl	%edx, 8(%esp)
	calll	CountDifferentLines
	leal	.L.str.1, %ecx
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	calll	printf
	movl	-20(%ebp), %ecx
	movl	-12(%ebp), %edx
	movl	-16(%ebp), %esi
	movl	%ecx, (%esp)
	movl	%edx, 4(%esp)
	movl	%esi, 8(%esp)
	movl	%eax, -28(%ebp)         # 4-byte Spill
	calll	CountDifferentRows
	leal	.L.str.2, %ecx
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	calll	printf
	movl	-20(%ebp), %ecx
	movl	%ecx, (%esp)
	movl	%eax, -32(%ebp)         # 4-byte Spill
	calll	free
	xorl	%eax, %eax
	addl	$52, %esp
	popl	%esi
	popl	%ebp
	retl
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"\n"
	.size	.L.str, 2

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"\320\232\320\276\320\273-\320\262\320\276 \321\201\321\202\321\200\320\276\320\272, \320\262\321\201\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\321\213 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \321\200\320\260\320\267\320\273\320\270\321\207\320\275\321\213: %d\n"
	.size	.L.str.1, 85

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"\320\232\320\276\320\273-\320\262\320\276 \321\201\321\202\320\276\320\273\320\261\321\206\320\276\320\262, \320\262\321\201\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\321\213 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \321\200\320\260\320\267\320\273\320\270\321\207\320\275\321\213: %d\n"
	.size	.L.str.2, 91


	.ident	"clang version 9.0.0-2 (tags/RELEASE_900/final)"
	.section	".note.GNU-stack","",@progbits

