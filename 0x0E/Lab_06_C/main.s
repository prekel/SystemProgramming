	.text
	.file	"main.ll"
	.globl	IsOnly                  # -- Begin function IsOnly
	.p2align	4, 0x90
	.type	IsOnly,@function
IsOnly:                                 # @IsOnly
	.cfi_startproc
# %bb.0:
	movslq	(%rdi), %r9
	testq	%r9, %r9
	movb	$1, %al
	jle	.LBB0_8
# %bb.1:
	movslq	4(%rdi), %r11
	movslq	%esi, %r8
	xorl	%r10d, %r10d
	testl	%r11d, %r11d
	jg	.LBB0_4
	.p2align	4, 0x90
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	incq	%r10
	cmpq	%r9, %r10
	jge	.LBB0_8
# %bb.3:                                #   in Loop: Header=BB0_2 Depth=1
	testl	%r11d, %r11d
	jle	.LBB0_2
.LBB0_4:
	movq	8(%rdi), %rcx
	movq	(%rcx,%r8,8), %rcx
	movl	(%rcx,%r10,4), %esi
	xorl	%edx, %edx
	.p2align	4, 0x90
.LBB0_5:                                # =>This Inner Loop Header: Depth=1
	cmpl	(%rcx,%rdx,4), %esi
	je	.LBB0_7
# %bb.6:                                #   in Loop: Header=BB0_5 Depth=1
	incq	%rdx
	cmpq	%r11, %rdx
	jl	.LBB0_5
	jmp	.LBB0_2
.LBB0_7:
	xorl	%eax, %eax
.LBB0_8:
                                        # kill: def $al killed $al killed $eax
	retq
.Lfunc_end0:
	.size	IsOnly, .Lfunc_end0-IsOnly
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	xorl	%eax, %eax
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function

	.section	".note.GNU-stack","",@progbits
