	.globl	ReadMatrix              // -- Begin function ReadMatrix
	.p2align	2
	.type	ReadMatrix,@function
ReadMatrix:                             // @ReadMatrix
// %bb.0:
	sub	sp, sp, #48             // =48
	stp	x29, x30, [sp, #32]     // 16-byte Folded Spill
	add	x29, sp, #32            // =32
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	str	w2, [sp, #16]
	str	wzr, [sp, #12]
.LBB1_1:                                // =>This Loop Header: Depth=1
                                        //     Child Loop BB1_3 Depth 2
	ldr	w8, [sp, #12]
	ldur	w9, [x29, #-12]
	cmp	w8, w9
	b.ge	.LBB1_8
// %bb.2:                               //   in Loop: Header=BB1_1 Depth=1
	str	wzr, [sp, #8]
.LBB1_3:                                //   Parent Loop BB1_1 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldr	w8, [sp, #8]
	ldr	w9, [sp, #16]
	cmp	w8, w9
	b.ge	.LBB1_6
// %bb.4:                               //   in Loop: Header=BB1_3 Depth=2
	ldur	x8, [x29, #-8]
	ldr	w9, [sp, #12]
	ldr	w10, [sp, #16]
	ldr	w11, [sp, #8]
	madd	w9, w9, w10, w11
	sxtw	x9, w9
	orr	x10, xzr, #0x4
	madd	x1, x9, x10, x8
	adrp	x0, .L.str
	add	x0, x0, :lo12:.L.str
	bl	__isoc99_scanf
// %bb.5:                               //   in Loop: Header=BB1_3 Depth=2
	ldr	w8, [sp, #8]
	add	w8, w8, #1              // =1
	str	w8, [sp, #8]
	b	.LBB1_3
.LBB1_6:                                //   in Loop: Header=BB1_1 Depth=1
	b	.LBB1_7
.LBB1_7:                                //   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1              // =1
	str	w8, [sp, #12]
	b	.LBB1_1
.LBB1_8:
	ldp	x29, x30, [sp, #32]     // 16-byte Folded Reload
	add	sp, sp, #48             // =48
	ret
.Lfunc_end1:
	.size	ReadMatrix, .Lfunc_end1-ReadMatrix
                                        // -- End function
	.globl	ReadMN                  // -- Begin function ReadMN
	.p2align	2
	.type	ReadMN,@function
ReadMN:                                 // @ReadMN
// %bb.0:
	sub	sp, sp, #32             // =32
	stp	x29, x30, [sp, #16]     // 16-byte Folded Spill
	add	x29, sp, #16            // =16
	str	x0, [sp, #8]
	str	x1, [sp]
	ldr	x1, [sp, #8]
	adrp	x0, .L.str
	add	x0, x0, :lo12:.L.str
	bl	__isoc99_scanf
	ldr	x1, [sp]
	adrp	x0, .L.str
	add	x0, x0, :lo12:.L.str
	bl	__isoc99_scanf
	ldp	x29, x30, [sp, #16]     // 16-byte Folded Reload
	add	sp, sp, #32             // =32
	ret
	
	.globl	main                    // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
// %bb.0:
	sub	sp, sp, #48             // =48
	stp	x29, x30, [sp, #32]     // 16-byte Folded Spill
	add	x29, sp, #32            // =32
	stur	wzr, [x29, #-4]
	sub	x0, x29, #8             // =8
	sub	x1, x29, #12            // =12
	bl	ReadMN
	ldur	w8, [x29, #-8]
	ldur	w9, [x29, #-12]
	mul	w8, w8, w9
	sbfiz	x0, x8, #2, #32
	bl	malloc
	str	x0, [sp, #8]
	ldr	x0, [sp, #8]
	ldur	w1, [x29, #-8]
	ldur	w2, [x29, #-12]
	bl	ReadMatrix
	ldr	x0, [sp, #8]
	ldur	w1, [x29, #-8]
	ldur	w2, [x29, #-12]
	bl	CountRow
	str	w0, [sp, #4]
	ldr	w1, [sp, #4]
	adrp	x0, .L.str.1
	add	x0, x0, :lo12:.L.str.1
	bl	printf
	ldr	x0, [sp, #8]
	ldur	w1, [x29, #-8]
	ldur	w2, [x29, #-12]
	bl	CountLine
	str	w0, [sp]
	ldr	w1, [sp]
	adrp	x0, .L.str.1
	add	x0, x0, :lo12:.L.str.1
	bl	printf
	ldr	x0, [sp, #8]
	bl	free
	mov	w0, wzr
	ldp	x29, x30, [sp, #32]     // 16-byte Folded Reload
	add	sp, sp, #48             // =48
	ret
	
.L.str:
	.asciz	"%d"
	
.L.str.1:
	.asciz	"%d\n"
