	.arch armv8-a
	.file	"MatrixIO.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"\320\222\320\262\320\265\320\264\320\270\321\202\320\265 M \320\270 N (\320\272\320\276\320\273-\320\262\320\276 \321\201\321\202\321\200\320\276\320\272 \320\270 \321\201\321\202\320\276\320\273\320\261\321\206\320\276\320\262, a[M][N]): "
	.align	3
.LC1:
	.string	"%d%d"
	.text
	.align	2
	.global	ReadMN
	.type	ReadMN, %function
ReadMN:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	x0, [sp, 24]
	str	x1, [sp, 16]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	ldr	x2, [sp, 16]
	ldr	x1, [sp, 24]
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	__isoc99_scanf
	nop
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	ReadMN, .-ReadMN
	.section	.rodata
	.align	3
.LC2:
	.string	"\320\222\320\262\320\265\320\264\320\270\321\202\320\265 a[%d][%d]: "
	.align	3
.LC3:
	.string	"%d"
	.text
	.align	2
	.global	ReadMatrix
	.type	ReadMatrix, %function
ReadMatrix:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	x0, [sp, 24]
	str	w1, [sp, 20]
	str	w2, [sp, 16]
	str	wzr, [sp, 40]
	b	.L3
.L6:
	str	wzr, [sp, 44]
	b	.L4
.L5:
	ldr	w2, [sp, 44]
	ldr	w1, [sp, 40]
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
	ldr	w1, [sp, 40]
	ldr	w0, [sp, 16]
	mul	w1, w1, w0
	ldr	w0, [sp, 44]
	add	w0, w1, w0
	sxtw	x0, w0
	lsl	x0, x0, 2
	ldr	x1, [sp, 24]
	add	x0, x1, x0
	mov	x1, x0
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	__isoc99_scanf
	ldr	w0, [sp, 44]
	add	w0, w0, 1
	str	w0, [sp, 44]
.L4:
	ldr	w1, [sp, 44]
	ldr	w0, [sp, 16]
	cmp	w1, w0
	blt	.L5
	ldr	w0, [sp, 40]
	add	w0, w0, 1
	str	w0, [sp, 40]
.L3:
	ldr	w1, [sp, 40]
	ldr	w0, [sp, 20]
	cmp	w1, w0
	blt	.L6
	nop
	nop
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE1:
	.size	ReadMatrix, .-ReadMatrix
	.section	.rodata
	.align	3
.LC4:
	.string	"\320\234\320\260\321\202\321\200\320\270\321\206\320\260 a[%d][%d]:\n"
	.align	3
.LC5:
	.string	"%d "
	.text
	.align	2
	.global	WriteMatrix
	.type	WriteMatrix, %function
WriteMatrix:
.LFB2:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	x0, [sp, 24]
	str	w1, [sp, 20]
	str	w2, [sp, 16]
	ldr	w2, [sp, 16]
	ldr	w1, [sp, 20]
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	printf
	str	wzr, [sp, 40]
	b	.L8
.L11:
	str	wzr, [sp, 44]
	b	.L9
.L10:
	ldr	w1, [sp, 40]
	ldr	w0, [sp, 16]
	mul	w1, w1, w0
	ldr	w0, [sp, 44]
	add	w0, w1, w0
	sxtw	x0, w0
	lsl	x0, x0, 2
	ldr	x1, [sp, 24]
	add	x0, x1, x0
	ldr	w0, [x0]
	mov	w1, w0
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
	ldr	w0, [sp, 44]
	add	w0, w0, 1
	str	w0, [sp, 44]
.L9:
	ldr	w1, [sp, 44]
	ldr	w0, [sp, 16]
	cmp	w1, w0
	blt	.L10
	mov	w0, 10
	bl	putchar
	ldr	w0, [sp, 40]
	add	w0, w0, 1
	str	w0, [sp, 40]
.L8:
	ldr	w1, [sp, 40]
	ldr	w0, [sp, 20]
	cmp	w1, w0
	blt	.L11
	nop
	nop
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE2:
	.size	WriteMatrix, .-WriteMatrix
	.ident	"GCC: (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008"
	.section	.note.GNU-stack,"",@progbits
