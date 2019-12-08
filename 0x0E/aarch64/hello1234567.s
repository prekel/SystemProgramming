	.text
	.file	"hello1234567.ll"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$helloWorldString, %edi
	movl	$123, %esi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	helloWorldString,@object # @helloWorldString
	.section	.rodata,"a",@progbits
	.globl	helloWorldString
helloWorldString:
	.asciz	"%d\n"
	.size	helloWorldString, 4

	.type	n,@object               # @n
	.globl	n
	.p2align	2
n:
	.long	1234                    # 0x4d2
	.size	n, 4


	.section	".note.GNU-stack","",@progbits
