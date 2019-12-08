	.globl	ReadMatrix
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
	
	.globl ReadMN
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
	
	.globl	main
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
	
.L.str:
	.asciz	"%d"
	
.L.str.1:
	.asciz	"%d\n"
	