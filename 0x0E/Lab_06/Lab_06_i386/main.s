	.text
	.file	"main.c"
	.globl	Check                   # -- Begin function Check
	.type	Check,@function
Check:                                  # @Check
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	movl	12(%ebp), %ecx
	movl	16(%ebp), %edx
	imull	%ecx, %edx
	movb	$1, %al
	testl	%edx, %edx
	jle	.LBB0_9
# %bb.1:                                # %.preheader
	movl	8(%ebp), %esi
	xorl	%edi, %edi
.LBB0_3:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_7 Depth 2
	leal	(%edi,%ecx), %eax
	cmpl	%edx, %eax
	jge	.LBB0_4
# %bb.5:                                #   in Loop: Header=BB0_3 Depth=1
	movl	(%esi,%edi,4), %ebx
	movl	%eax, %edi
.LBB0_7:                                #   Parent Loop BB0_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpl	(%esi,%edi,4), %ebx
	je	.LBB0_8
# %bb.6:                                #   in Loop: Header=BB0_7 Depth=2
	addl	%ecx, %edi
	cmpl	%edx, %edi
	jl	.LBB0_7
# %bb.2:                                #   in Loop: Header=BB0_3 Depth=1
	cmpl	%edx, %eax
	movl	%eax, %edi
	jl	.LBB0_3
.LBB0_4:
	movb	$1, %al
	jmp	.LBB0_9
.LBB0_8:
	xorl	%eax, %eax
.LBB0_9:
                                        # kill: def $al killed $al killed $eax
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
.Lfunc_end0:
	.size	Check, .Lfunc_end0-Check
                                        # -- End function
	.globl	ReadMatrix              # -- Begin function ReadMatrix
	.type	ReadMatrix,@function
ReadMatrix:                             # @ReadMatrix
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$8, %esp
	cmpl	$0, 12(%ebp)
	jle	.LBB1_4
# %bb.1:
	movl	16(%ebp), %eax
	movl	8(%ebp), %ebx
	leal	(,%eax,4), %eax
	movl	%eax, -16(%ebp)         # 4-byte Spill
	xorl	%edi, %edi
.LBB1_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_5 Depth 2
	movl	16(%ebp), %esi
	testl	%esi, %esi
	movl	%ebx, -20(%ebp)         # 4-byte Spill
	jle	.LBB1_3
.LBB1_5:                                #   Parent Loop BB1_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	pushl	%ebx
	pushl	$.L.str
	calll	__isoc99_scanf
	addl	$8, %esp
	addl	$4, %ebx
	decl	%esi
	jne	.LBB1_5
.LBB1_3:                                #   in Loop: Header=BB1_2 Depth=1
	incl	%edi
	movl	-20(%ebp), %ebx         # 4-byte Reload
	addl	-16(%ebp), %ebx         # 4-byte Folded Reload
	cmpl	12(%ebp), %edi
	jne	.LBB1_2
.LBB1_4:
	addl	$8, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
.Lfunc_end1:
	.size	ReadMatrix, .Lfunc_end1-ReadMatrix
                                        # -- End function
	.globl	ReadMN                  # -- Begin function ReadMN
	.type	ReadMN,@function
ReadMN:                                 # @ReadMN
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	12(%ebp), %esi
	movl	$.L.str, %edi
	pushl	8(%ebp)
	pushl	%edi
	calll	__isoc99_scanf
	addl	$8, %esp
	pushl	%esi
	pushl	%edi
	calll	__isoc99_scanf
	addl	$8, %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	retl
.Lfunc_end2:
	.size	ReadMN, .Lfunc_end2-ReadMN
                                        # -- End function
	.globl	CountRow                # -- Begin function CountRow
	.type	CountRow,@function
CountRow:                               # @CountRow
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$28, %esp
	movl	16(%ebp), %edi
	testl	%edi, %edi
	jle	.LBB3_1
# %bb.3:
	movl	8(%ebp), %ecx
	movl	12(%ebp), %esi
	imull	%edi, %esi
	testl	%esi, %esi
	setle	%al
	movl	%esi, -36(%ebp)         # 4-byte Spill
	cmpl	%edi, %esi
	setle	%ah
	orb	%al, %ah
	movb	%ah, -13(%ebp)          # 1-byte Spill
	leal	(%ecx,%edi,4), %esi
	leal	(,%edi,4), %eax
	movl	%eax, -40(%ebp)         # 4-byte Spill
	movl	$0, -20(%ebp)           # 4-byte Folded Spill
	xorl	%ebx, %ebx
.LBB3_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_7 Depth 2
                                        #       Child Loop BB3_9 Depth 3
	cmpb	$0, -13(%ebp)           # 1-byte Folded Reload
	je	.LBB3_5
.LBB3_11:                               #   in Loop: Header=BB3_4 Depth=1
	incl	-20(%ebp)               # 4-byte Folded Spill
	jmp	.LBB3_12
.LBB3_5:                                # %.preheader
                                        #   in Loop: Header=BB3_4 Depth=1
	movl	8(%ebp), %eax
	leal	(%eax,%ebx,4), %edx
	xorl	%eax, %eax
	movl	%esi, -24(%ebp)         # 4-byte Spill
	movl	%edi, %ecx
	movl	%esi, -32(%ebp)         # 4-byte Spill
	movl	%ebx, -28(%ebp)         # 4-byte Spill
.LBB3_7:                                #   Parent Loop BB3_4 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB3_9 Depth 3
	movl	%edi, %esi
	movl	(%edx,%eax,4), %ebx
	movl	%ecx, %eax
	xorl	%ecx, %ecx
.LBB3_9:                                #   Parent Loop BB3_4 Depth=1
                                        #     Parent Loop BB3_7 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	movl	-24(%ebp), %edi         # 4-byte Reload
	cmpl	(%edi,%ecx,4), %ebx
	je	.LBB3_10
# %bb.8:                                #   in Loop: Header=BB3_9 Depth=3
	addl	%esi, %ecx
	movl	%edx, %edi
	leal	(%eax,%ecx), %edx
	cmpl	-36(%ebp), %edx         # 4-byte Folded Reload
	movl	%edi, %edx
	jl	.LBB3_9
# %bb.6:                                #   in Loop: Header=BB3_7 Depth=2
	movl	%esi, %edi
	leal	(%eax,%esi), %ecx
	movl	-24(%ebp), %esi         # 4-byte Reload
	addl	-40(%ebp), %esi         # 4-byte Folded Reload
	movl	%esi, -24(%ebp)         # 4-byte Spill
	cmpl	-36(%ebp), %ecx         # 4-byte Folded Reload
	movl	-32(%ebp), %esi         # 4-byte Reload
	movl	-28(%ebp), %ebx         # 4-byte Reload
	jl	.LBB3_7
	jmp	.LBB3_11
.LBB3_10:                               #   in Loop: Header=BB3_4 Depth=1
	movl	%esi, %edi
	movl	-32(%ebp), %esi         # 4-byte Reload
	movl	-28(%ebp), %ebx         # 4-byte Reload
.LBB3_12:                               #   in Loop: Header=BB3_4 Depth=1
	incl	%ebx
	addl	$4, %esi
	cmpl	%edi, %ebx
	jne	.LBB3_4
	jmp	.LBB3_2
.LBB3_1:
	movl	$0, -20(%ebp)           # 4-byte Folded Spill
.LBB3_2:
	movl	-20(%ebp), %eax         # 4-byte Reload
	addl	$28, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
.Lfunc_end3:
	.size	CountRow, .Lfunc_end3-CountRow
                                        # -- End function
	.globl	CountLine               # -- Begin function CountLine
	.type	CountLine,@function
CountLine:                              # @CountLine
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$20, %esp
	cmpl	$0, 12(%ebp)
	jle	.LBB4_1
# %bb.3:
	movl	16(%ebp), %ecx
	movl	8(%ebp), %eax
	leal	(,%ecx,4), %ecx
	movl	%ecx, -28(%ebp)         # 4-byte Spill
	movl	$0, -16(%ebp)           # 4-byte Folded Spill
	movl	%eax, %ebx
	movl	$0, -20(%ebp)           # 4-byte Folded Spill
.LBB4_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB4_7 Depth 2
                                        #       Child Loop BB4_9 Depth 3
	cmpl	$2, 16(%ebp)
	jge	.LBB4_5
.LBB4_11:                               #   in Loop: Header=BB4_4 Depth=1
	incl	-16(%ebp)               # 4-byte Folded Spill
	jmp	.LBB4_12
.LBB4_5:                                # %.preheader
                                        #   in Loop: Header=BB4_4 Depth=1
	movl	-20(%ebp), %eax         # 4-byte Reload
	imull	16(%ebp), %eax
	movl	8(%ebp), %ecx
	leal	(%ecx,%eax,4), %edx
	xorl	%edi, %edi
	movl	%ebx, %esi
	xorl	%eax, %eax
	incl	%eax
	movl	%ebx, -24(%ebp)         # 4-byte Spill
.LBB4_7:                                #   Parent Loop BB4_4 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB4_9 Depth 3
	movl	%eax, -32(%ebp)         # 4-byte Spill
	movl	(%edx,%edi,4), %eax
	xorl	%ebx, %ebx
	incl	%ebx
.LBB4_9:                                #   Parent Loop BB4_4 Depth=1
                                        #     Parent Loop BB4_7 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	cmpl	(%esi,%ebx,4), %eax
	je	.LBB4_10
# %bb.8:                                #   in Loop: Header=BB4_9 Depth=3
	leal	1(%edi,%ebx), %ecx
	incl	%ebx
	cmpl	16(%ebp), %ecx
	jl	.LBB4_9
# %bb.6:                                #   in Loop: Header=BB4_7 Depth=2
	movl	-32(%ebp), %eax         # 4-byte Reload
	incl	%eax
	incl	%edi
	addl	$4, %esi
	cmpl	16(%ebp), %eax
	movl	-24(%ebp), %ebx         # 4-byte Reload
	jl	.LBB4_7
	jmp	.LBB4_11
.LBB4_10:                               #   in Loop: Header=BB4_4 Depth=1
	movl	-24(%ebp), %ebx         # 4-byte Reload
.LBB4_12:                               #   in Loop: Header=BB4_4 Depth=1
	movl	-20(%ebp), %eax         # 4-byte Reload
	incl	%eax
	addl	-28(%ebp), %ebx         # 4-byte Folded Reload
	movl	%eax, -20(%ebp)         # 4-byte Spill
	cmpl	12(%ebp), %eax
	jne	.LBB4_4
	jmp	.LBB4_2
.LBB4_1:
	movl	$0, -16(%ebp)           # 4-byte Folded Spill
.LBB4_2:
	movl	-16(%ebp), %eax         # 4-byte Reload
	addl	$20, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
.Lfunc_end4:
	.size	CountLine, .Lfunc_end4-CountLine
                                        # -- End function
	.globl	main                    # -- Begin function main
	.type	main,@function
main:                                   # @main
# %bb.0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$8, %esp
	leal	-20(%ebp), %ebx
	movl	$.L.str, %edi
	pushl	%ebx
	pushl	%edi
	calll	__isoc99_scanf
	addl	$8, %esp
	leal	-16(%ebp), %esi
	pushl	%esi
	pushl	%edi
	calll	__isoc99_scanf
	addl	$8, %esp
	movl	(%ebx), %edi
	movl	(%esi), %ebx
	movl	%edi, %eax
	imull	%ebx, %eax
	shll	$2, %eax
	pushl	%eax
	calll	malloc
	addl	$4, %esp
	movl	%eax, %esi
	pushl	%ebx
	pushl	%edi
	pushl	%eax
	calll	ReadMatrix
	addl	$12, %esp
	leal	-16(%ebp), %ebx
	pushl	(%ebx)
	leal	-20(%ebp), %edi
	pushl	(%edi)
	pushl	%esi
	calll	CountRow
	addl	$12, %esp
	movl	$.L.str.1, %ecx
	pushl	%eax
	pushl	%ecx
	calll	printf
	addl	$8, %esp
	pushl	(%ebx)
	pushl	(%edi)
	pushl	%esi
	calll	CountLine
	addl	$12, %esp
	pushl	%eax
	movl	$.L.str.1, %eax
	pushl	%eax
	calll	printf
	addl	$8, %esp
	pushl	%esi
	calll	free
	addl	$4, %esp
	xorl	%eax, %eax
	addl	$8, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	retl
.Lfunc_end5:
	.size	main, .Lfunc_end5-main
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d"
	.size	.L.str, 3

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"%d\n"
	.size	.L.str.1, 4


	.ident	"clang version 8.0.0-3~ubuntu18.04.1 (tags/RELEASE_800/final)"
	.section	".note.GNU-stack","",@progbits
