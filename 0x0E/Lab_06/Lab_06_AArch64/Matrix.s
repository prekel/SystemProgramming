	.globl	Check
Check:                                  // @Check
// %bb.0:
	sub	sp, sp, #48             // =48
	str	x0, [sp, #32]
	str	w1, [sp, #28]
	str	w2, [sp, #24]
	ldr	w8, [sp, #24]
	ldr	w9, [sp, #28]
	mul	w8, w8, w9
	str	w8, [sp, #20]
	str	wzr, [sp, #16]
.LBB0_1:                                // =>This Loop Header: Depth=1
                                        //     Child Loop BB0_3 Depth 2
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #20]
	cmp	w8, w9
	b.ge	.LBB0_10
// %bb.2:                               //   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #16]
	ldr	w9, [sp, #28]
	add	w8, w8, w9
	str	w8, [sp, #12]
.LBB0_3:                                //   Parent Loop BB0_1 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #20]
	cmp	w8, w9
	b.ge	.LBB0_8
// %bb.4:                               //   in Loop: Header=BB0_3 Depth=2
	ldr	x8, [sp, #32]
	ldrsw	x9, [sp, #16]
	orr	x10, xzr, #0x4
	madd	x8, x9, x10, x8
	ldr	w8, [x8]
	ldr	x9, [sp, #32]
	ldrsw	x10, [sp, #12]
	orr	x11, xzr, #0x4
	madd	x9, x10, x11, x9
	ldr	w9, [x9]
	cmp	w8, w9
	b.ne	.LBB0_6
// %bb.5:
	strb	wzr, [sp, #47]
	b	.LBB0_11
.LBB0_6:                                //   in Loop: Header=BB0_3 Depth=2
	b	.LBB0_7
.LBB0_7:                                //   in Loop: Header=BB0_3 Depth=2
	ldr	w8, [sp, #28]
	ldr	w9, [sp, #12]
	add	w8, w9, w8
	str	w8, [sp, #12]
	b	.LBB0_3
.LBB0_8:                                //   in Loop: Header=BB0_1 Depth=1
	b	.LBB0_9
.LBB0_9:                                //   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #28]
	ldr	w9, [sp, #16]
	add	w8, w9, w8
	str	w8, [sp, #16]
	b	.LBB0_1
.LBB0_10:
	orr	w8, wzr, #0x1
	and	w8, w8, #0x1
	strb	w8, [sp, #47]
.LBB0_11:
	ldrb	w0, [sp, #47]
	add	sp, sp, #48             // =48
	ret


	.globl	CountRow
CountRow:                               // @CountRow
// %bb.0:
	sub	sp, sp, #48             // =48
	stp	x29, x30, [sp, #32]     // 16-byte Folded Spill
	add	x29, sp, #32            // =32
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	str	w2, [sp, #16]
	str	wzr, [sp, #12]
	str	wzr, [sp, #8]
.LBB3_1:                                // =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #8]
	ldr	w9, [sp, #16]
	cmp	w8, w9
	b.ge	.LBB3_6
// %bb.2:                               //   in Loop: Header=BB3_1 Depth=1
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #8]
	orr	x10, xzr, #0x4
	madd	x0, x9, x10, x8
	ldr	w1, [sp, #16]
	ldur	w2, [x29, #-12]
	bl	Check
	and	w8, w0, #0x1
	strb	w8, [sp, #4]
	ldrb	w8, [sp, #4]
	tbz	w8, #0, .LBB3_4
// %bb.3:                               //   in Loop: Header=BB3_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1              // =1
	str	w8, [sp, #12]
.LBB3_4:                                //   in Loop: Header=BB3_1 Depth=1
	b	.LBB3_5
.LBB3_5:                                //   in Loop: Header=BB3_1 Depth=1
	ldr	w8, [sp, #8]
	add	w8, w8, #1              // =1
	str	w8, [sp, #8]
	b	.LBB3_1
.LBB3_6:
	ldr	w0, [sp, #12]
	ldp	x29, x30, [sp, #32]     // 16-byte Folded Reload
	add	sp, sp, #48             // =48
	ret
                                        // -- End function
	.globl	CountLine
CountLine:                              // @CountLine
// %bb.0:
	sub	sp, sp, #48             // =48
	stp	x29, x30, [sp, #32]     // 16-byte Folded Spill
	add	x29, sp, #32            // =32
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	str	w2, [sp, #16]
	str	wzr, [sp, #12]
	str	wzr, [sp, #8]
.LBB4_1:                                // =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #8]
	ldur	w9, [x29, #-12]
	cmp	w8, w9
	b.ge	.LBB4_6
// %bb.2:                               //   in Loop: Header=BB4_1 Depth=1
	ldur	x8, [x29, #-8]
	ldr	w9, [sp, #8]
	ldr	w10, [sp, #16]
	mul	w9, w9, w10
	sxtw	x9, w9
	orr	x10, xzr, #0x4
	madd	x0, x9, x10, x8
	ldr	w2, [sp, #16]
	orr	w1, wzr, #0x1
	bl	Check
	and	w8, w0, #0x1
	strb	w8, [sp, #4]
	ldrb	w8, [sp, #4]
	tbz	w8, #0, .LBB4_4
// %bb.3:                               //   in Loop: Header=BB4_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1              // =1
	str	w8, [sp, #12]
.LBB4_4:                                //   in Loop: Header=BB4_1 Depth=1
	b	.LBB4_5
.LBB4_5:                                //   in Loop: Header=BB4_1 Depth=1
	ldr	w8, [sp, #8]
	add	w8, w8, #1              // =1
	str	w8, [sp, #8]
	b	.LBB4_1
.LBB4_6:
	ldr	w0, [sp, #12]
	ldp	x29, x30, [sp, #32]     // 16-byte Folded Reload
	add	sp, sp, #48             // =48
	ret
                                        // -- End function

.L.str:
	.asciz	"%d"

.L.str.1:
	.asciz	"%d\n"
