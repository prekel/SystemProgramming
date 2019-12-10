	.arch armv8-a
	.file	"main.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"\320\232\320\276\320\273-\320\262\320\276 \321\201\321\202\321\200\320\276\320\272, \320\262\321\201\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\321\213 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \321\200\320\260\320\267\320\273\320\270\321\207\320\275\321\213: %d\n"
	.align	3
.LC1:
	.string	"\320\232\320\276\320\273-\320\262\320\276 \321\201\321\202\320\276\320\273\320\261\321\206\320\276\320\262, \320\262\321\201\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\321\213 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \321\200\320\260\320\267\320\273\320\270\321\207\320\275\321\213: %d\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -128]!
	.cfi_def_cfa_offset 128
	.cfi_offset 29, -128
	.cfi_offset 30, -120
	mov	x29, sp
	.cfi_def_cfa_register 29
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	sub	sp, sp, #16
	.cfi_offset 19, -112
	.cfi_offset 20, -104
	.cfi_offset 21, -96
	.cfi_offset 22, -88
	.cfi_offset 23, -80
	.cfi_offset 24, -72
	.cfi_offset 25, -64
	.cfi_offset 26, -56
	.cfi_offset 27, -48
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x1, [x0]
	str	x1, [x29, 120]
	mov	x1,0
	mov	x0, sp
	mov	x19, x0
	add	x1, x29, 100
	add	x0, x29, 96
	bl	ReadMN
	ldr	w1, [x29, 96]
	ldr	w0, [x29, 100]
	mul	w0, w1, w0
	sxtw	x1, w0
	sub	x1, x1, #1
	str	x1, [x29, 104]
	sxtw	x1, w0
	mov	x26, x1
	mov	x27, 0
	lsr	x1, x26, 59
	lsl	x23, x27, 5
	orr	x23, x1, x23
	lsl	x22, x26, 5
	sxtw	x1, w0
	mov	x24, x1
	mov	x25, 0
	lsr	x1, x24, 59
	lsl	x21, x25, 5
	orr	x21, x1, x21
	lsl	x20, x24, 5
	sxtw	x0, w0
	lsl	x0, x0, 2
	add	x0, x0, 15
	lsr	x0, x0, 4
	lsl	x0, x0, 4
	and	x1, x0, -65536
	sub	x1, sp, x1
.L2:
	cmp	sp, x1
	beq	.L3
	sub	sp, sp, #65536
	str	xzr, [sp, 1024]
	b	.L2
.L3:
	and	x1, x0, 65535
	sub	sp, sp, x1
	str	xzr, [sp]
	and	x0, x0, 65535
	cmp	x0, 1024
	bcc	.L4
	str	xzr, [sp, 1024]
.L4:
	add	x0, sp, 16
	add	x0, x0, 3
	lsr	x0, x0, 2
	lsl	x0, x0, 2
	str	x0, [x29, 112]
	ldr	x0, [x29, 112]
	ldr	w1, [x29, 96]
	ldr	w2, [x29, 100]
	bl	ReadMatrix
	mov	w0, 10
	bl	putchar
	ldr	x0, [x29, 112]
	ldr	w1, [x29, 96]
	ldr	w2, [x29, 100]
	bl	WriteMatrix
	ldr	x0, [x29, 112]
	ldr	w1, [x29, 96]
	ldr	w2, [x29, 100]
	bl	CountDifferentLines
	mov	w1, w0
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	ldr	x0, [x29, 112]
	ldr	w1, [x29, 96]
	ldr	w2, [x29, 100]
	bl	CountDifferentRows
	mov	w1, w0
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
	mov	w0, 0
	mov	sp, x19
	mov	w1, w0
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x2, [x29, 120]
	ldr	x0, [x0]
	eor	x0, x2, x0
	cmp	x0, 0
	beq	.L6
	bl	__stack_chk_fail
.L6:
	mov	w0, w1
	mov	sp, x29
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 128
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008"
	.section	.note.GNU-stack,"",@progbits
