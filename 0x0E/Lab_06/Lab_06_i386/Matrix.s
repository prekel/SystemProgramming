	.text
	.file	"Matrix.c"
	.globl	CheckAllDifferent       # -- Begin function CheckAllDifferent
	.p2align	4, 0x90
	.type	CheckAllDifferent,@function
CheckAllDifferent:                      # @CheckAllDifferent
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$16, %esp
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	16(%ebp), %esi
	imull	12(%ebp), %esi
	movl	%esi, -12(%ebp)
	movl	$0, -16(%ebp)
.LBB0_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	movl	-16(%ebp), %eax
	cmpl	-12(%ebp), %eax
	jge	.LBB0_10
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movl	-16(%ebp), %eax
	addl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
.LBB0_3:                                #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	-20(%ebp), %eax
	cmpl	-12(%ebp), %eax
	jge	.LBB0_8
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=2
	movl	8(%ebp), %eax
	movl	-16(%ebp), %ecx
	movl	(%eax,%ecx,4), %eax
	movl	8(%ebp), %ecx
	movl	-20(%ebp), %edx
	cmpl	(%ecx,%edx,4), %eax
	jne	.LBB0_6
# %bb.5:
	movb	$0, -5(%ebp)
	jmp	.LBB0_11
.LBB0_6:                                #   in Loop: Header=BB0_3 Depth=2
	jmp	.LBB0_7
.LBB0_7:                                #   in Loop: Header=BB0_3 Depth=2
	movl	12(%ebp), %eax
	addl	-20(%ebp), %eax
	movl	%eax, -20(%ebp)
	jmp	.LBB0_3
.LBB0_8:                                #   in Loop: Header=BB0_1 Depth=1
	jmp	.LBB0_9
.LBB0_9:                                #   in Loop: Header=BB0_1 Depth=1
	movl	12(%ebp), %eax
	addl	-16(%ebp), %eax
	movl	%eax, -16(%ebp)
	jmp	.LBB0_1
.LBB0_10:
	movb	$1, -5(%ebp)
.LBB0_11:
	movb	-5(%ebp), %al
	andb	$1, %al
	movzbl	%al, %eax
	addl	$16, %esp
	popl	%esi
	popl	%ebp
	retl
.Lfunc_end0:
	.size	CheckAllDifferent, .Lfunc_end0-CheckAllDifferent
                                        # -- End function
	.globl	CountDifferentLines     # -- Begin function CountDifferentLines
	.p2align	4, 0x90
	.type	CountDifferentLines,@function
CountDifferentLines:                    # @CountDifferentLines
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	movl	-8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	.LBB1_6
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
	movl	8(%ebp), %eax
	movl	-8(%ebp), %ecx
	imull	16(%ebp), %ecx
	shll	$2, %ecx
	addl	%ecx, %eax
	movl	16(%ebp), %ecx
	movl	%eax, (%esp)
	movl	$1, 4(%esp)
	movl	%ecx, 8(%esp)
	calll	CheckAllDifferent
	andb	$1, %al
	movb	%al, -9(%ebp)
	testb	$1, -9(%ebp)
	je	.LBB1_4
# %bb.3:                                #   in Loop: Header=BB1_1 Depth=1
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
.LBB1_4:                                #   in Loop: Header=BB1_1 Depth=1
	jmp	.LBB1_5
.LBB1_5:                                #   in Loop: Header=BB1_1 Depth=1
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	.LBB1_1
.LBB1_6:
	movl	-4(%ebp), %eax
	addl	$24, %esp
	popl	%ebp
	retl
.Lfunc_end1:
	.size	CountDifferentLines, .Lfunc_end1-CountDifferentLines
                                        # -- End function
	.globl	CountDifferentRows      # -- Begin function CountDifferentRows
	.p2align	4, 0x90
	.type	CountDifferentRows,@function
CountDifferentRows:                     # @CountDifferentRows
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
.LBB2_1:                                # =>This Inner Loop Header: Depth=1
	movl	-8(%ebp), %eax
	cmpl	16(%ebp), %eax
	jge	.LBB2_6
# %bb.2:                                #   in Loop: Header=BB2_1 Depth=1
	movl	8(%ebp), %eax
	movl	-8(%ebp), %ecx
	shll	$2, %ecx
	addl	%ecx, %eax
	movl	16(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%ecx, 4(%esp)
	movl	%edx, 8(%esp)
	calll	CheckAllDifferent
	andb	$1, %al
	movb	%al, -9(%ebp)
	testb	$1, -9(%ebp)
	je	.LBB2_4
# %bb.3:                                #   in Loop: Header=BB2_1 Depth=1
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
.LBB2_4:                                #   in Loop: Header=BB2_1 Depth=1
	jmp	.LBB2_5
.LBB2_5:                                #   in Loop: Header=BB2_1 Depth=1
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	.LBB2_1
.LBB2_6:
	movl	-4(%ebp), %eax
	addl	$24, %esp
	popl	%ebp
	retl
.Lfunc_end2:
	.size	CountDifferentRows, .Lfunc_end2-CountDifferentRows
                                        # -- End function

	.ident	"clang version 9.0.0-2 (tags/RELEASE_900/final)"
	.section	".note.GNU-stack","",@progbits

