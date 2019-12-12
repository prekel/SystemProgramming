	.text
	.file	"MatrixIO.c"
	.globl	ReadMN                  # -- Begin function ReadMN
	.p2align	4, 0x90
	.type	ReadMN,@function
ReadMN:                                 # @ReadMN
# %bb.0:
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
.Lfunc_end0:
	.size	ReadMN, .Lfunc_end0-ReadMN
                                        # -- End function
	.globl	ReadMatrix              # -- Begin function ReadMatrix
	.p2align	4, 0x90
	.type	ReadMatrix,@function
ReadMatrix:                             # @ReadMatrix
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	$0, -4(%ebp)
.LBB1_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_3 Depth 2
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	.LBB1_8
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
	movl	$0, -8(%ebp)
.LBB1_3:                                #   Parent Loop BB1_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-8(%ebp), %eax
	cmpl	16(%ebp), %eax
	jge	.LBB1_6
# %bb.4:                                #   in Loop: Header=BB1_3 Depth=2
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
	movl	%eax, -12(%ebp)         # 4-byte Spill
	calll	__isoc99_scanf
# %bb.5:                                #   in Loop: Header=BB1_3 Depth=2
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	.LBB1_3
.LBB1_6:                                #   in Loop: Header=BB1_1 Depth=1
	jmp	.LBB1_7
.LBB1_7:                                #   in Loop: Header=BB1_1 Depth=1
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
	jmp	.LBB1_1
.LBB1_8:
	addl	$24, %esp
	popl	%ebp
	retl
.Lfunc_end1:
	.size	ReadMatrix, .Lfunc_end1-ReadMatrix
                                        # -- End function
	.globl	WriteMatrix             # -- Begin function WriteMatrix
	.p2align	4, 0x90
	.type	WriteMatrix,@function
WriteMatrix:                            # @WriteMatrix
# %bb.0:
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
	movl	%eax, -24(%ebp)         # 4-byte Spill
	movl	%ecx, -28(%ebp)         # 4-byte Spill
	movl	%edx, -32(%ebp)         # 4-byte Spill
	calll	printf
	movl	$0, -16(%ebp)
.LBB2_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_3 Depth 2
	movl	-16(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	.LBB2_8
# %bb.2:                                #   in Loop: Header=BB2_1 Depth=1
	movl	$0, -20(%ebp)
.LBB2_3:                                #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-20(%ebp), %eax
	cmpl	16(%ebp), %eax
	jge	.LBB2_6
# %bb.4:                                #   in Loop: Header=BB2_3 Depth=2
	movl	8(%ebp), %eax
	movl	-16(%ebp), %ecx
	imull	16(%ebp), %ecx
	addl	-20(%ebp), %ecx
	movl	(%eax,%ecx,4), %eax
	leal	.L.str.5, %ecx
	movl	%ecx, (%esp)
	movl	%eax, 4(%esp)
	calll	printf
# %bb.5:                                #   in Loop: Header=BB2_3 Depth=2
	movl	-20(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -20(%ebp)
	jmp	.LBB2_3
.LBB2_6:                                #   in Loop: Header=BB2_1 Depth=1
	leal	.L.str.6, %eax
	movl	%eax, (%esp)
	calll	printf
# %bb.7:                                #   in Loop: Header=BB2_1 Depth=1
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
.Lfunc_end2:
	.size	WriteMatrix, .Lfunc_end2-WriteMatrix
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"\320\222\320\262\320\265\320\264\320\270\321\202\320\265 M \320\270 N (\320\272\320\276\320\273-\320\262\320\276 \321\201\321\202\321\200\320\276\320\272 \320\270 \321\201\321\202\320\276\320\273\320\261\321\206\320\276\320\262, a[M][N]): "
	.size	.L.str, 78

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"%d%d"
	.size	.L.str.1, 5

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"\320\222\320\262\320\265\320\264\320\270\321\202\320\265 a[%d][%d]: "
	.size	.L.str.2, 27

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"%d"
	.size	.L.str.3, 3

	.type	.L.str.4,@object        # @.str.4
.L.str.4:
	.asciz	"\320\234\320\260\321\202\321\200\320\270\321\206\320\260 a[%d][%d]:\n"
	.size	.L.str.4, 27

	.type	.L.str.5,@object        # @.str.5
.L.str.5:
	.asciz	"%d "
	.size	.L.str.5, 4

	.type	.L.str.6,@object        # @.str.6
.L.str.6:
	.asciz	"\n"
	.size	.L.str.6, 2


	.ident	"clang version 9.0.0-2 (tags/RELEASE_900/final)"
	.section	".note.GNU-stack","",@progbits

