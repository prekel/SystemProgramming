	.arch armv8-a
	.file	"Matrix.c"
	.text
	.align	2
	.global	CheckAllDifferent
	.type	CheckAllDifferent, %function
CheckAllDifferent:
.LFB6:
	.cfi_startproc
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, 8]
	str	w1, [sp, 4]
	str	w2, [sp]
	ldr	w1, [sp]
	ldr	w0, [sp, 4]
	mul	w0, w1, w0
	str	w0, [sp, 28]
	str	wzr, [sp, 20]
	b	.L2
.L7:
	ldr	w1, [sp, 20]
	ldr	w0, [sp, 4]
	add	w0, w1, w0
	str	w0, [sp, 24]
	b	.L3
.L6:
	ldrsw	x0, [sp, 20]
	lsl	x0, x0, 2
	ldr	x1, [sp, 8]
	add	x0, x1, x0
	ldr	w1, [x0]
	ldrsw	x0, [sp, 24]
	lsl	x0, x0, 2
	ldr	x2, [sp, 8]
	add	x0, x2, x0
	ldr	w0, [x0]
	cmp	w1, w0
	bne	.L4
	mov	w0, 0
	b	.L5
.L4:
	ldr	w1, [sp, 24]
	ldr	w0, [sp, 4]
	add	w0, w1, w0
	str	w0, [sp, 24]
.L3:
	ldr	w1, [sp, 24]
	ldr	w0, [sp, 28]
	cmp	w1, w0
	blt	.L6
	ldr	w1, [sp, 20]
	ldr	w0, [sp, 4]
	add	w0, w1, w0
	str	w0, [sp, 20]
.L2:
	ldr	w1, [sp, 20]
	ldr	w0, [sp, 28]
	cmp	w1, w0
	blt	.L7
	mov	w0, 1
.L5:
	add	sp, sp, 32
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	CheckAllDifferent, .-CheckAllDifferent
	.align	2
	.global	CountDifferentLines
	.type	CountDifferentLines, %function
CountDifferentLines:
.LFB7:
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
	str	wzr, [sp, 44]
	b	.L9
.L11:
	ldr	w1, [sp, 44]
	ldr	w0, [sp, 16]
	mul	w0, w1, w0
	sxtw	x0, w0
	lsl	x0, x0, 2
	ldr	x1, [sp, 24]
	add	x0, x1, x0
	ldr	w2, [sp, 16]
	mov	w1, 1
	bl	CheckAllDifferent
	strb	w0, [sp, 39]
	ldrb	w0, [sp, 39]
	cmp	w0, 0
	beq	.L10
	ldr	w0, [sp, 40]
	add	w0, w0, 1
	str	w0, [sp, 40]
.L10:
	ldr	w0, [sp, 44]
	add	w0, w0, 1
	str	w0, [sp, 44]
.L9:
	ldr	w1, [sp, 44]
	ldr	w0, [sp, 20]
	cmp	w1, w0
	blt	.L11
	ldr	w0, [sp, 40]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE7:
	.size	CountDifferentLines, .-CountDifferentLines
	.align	2
	.global	CountDifferentRows
	.type	CountDifferentRows, %function
CountDifferentRows:
.LFB8:
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
	str	wzr, [sp, 44]
	b	.L14
.L16:
	ldrsw	x0, [sp, 44]
	lsl	x0, x0, 2
	ldr	x1, [sp, 24]
	add	x0, x1, x0
	ldr	w2, [sp, 20]
	ldr	w1, [sp, 16]
	bl	CheckAllDifferent
	strb	w0, [sp, 39]
	ldrb	w0, [sp, 39]
	cmp	w0, 0
	beq	.L15
	ldr	w0, [sp, 40]
	add	w0, w0, 1
	str	w0, [sp, 40]
.L15:
	ldr	w0, [sp, 44]
	add	w0, w0, 1
	str	w0, [sp, 44]
.L14:
	ldr	w1, [sp, 44]
	ldr	w0, [sp, 16]
	cmp	w1, w0
	blt	.L16
	ldr	w0, [sp, 40]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8:
	.size	CountDifferentRows, .-CountDifferentRows
	.ident	"GCC: (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008"
	.section	.note.GNU-stack,"",@progbits
