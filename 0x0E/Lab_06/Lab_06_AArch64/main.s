.text
    .global	main
main:
    str x30, [sp, #-8]!
    str x19, [sp, #-8]!
    str x20, [sp, #-8]!
    str x21, [sp, #-8]!
	
	sub sp, sp, #8 								// 

	mov x0, sp
	add sp, sp, #4
	mov x1, sp
	sub sp, sp, #4
	bl ReadMN	
	
	ldr w19, [sp]
	add sp, sp, #4
	ldr w20, [sp]
	add sp, sp, #4

	mul w0, w19, w20							// w0 <- w19 * w20
	mov w1, #4
	mul w0, w0, w1								// w0 *= 4
	bl malloc									// call malloc

	mov x21, x0									// x21 <- x0

	//mov w0, #1
	//mov x1, #0
	//str w0, [x21, x1, lsl #2]					// x21[0] <- 1
	//mov w0, #5
	//mov x1, #1
	//str w0, [x21, x1, lsl #2]					// x21[1] <- 5
	//mov w0, #3
	//mov x1, #2
	//str w0, [x21, x1, lsl #2]					// x21[2] <- 3
	//mov w0, #4
	//mov x1, #3
	//str w0, [x21, x1, lsl #2]					// x21[3] <- 4
	//mov w0, #5
	//mov x1, #4
	//str w0, [x21, x1, lsl #2]					// x21[4] <- 5
	//mov w0, #6
	//mov x1, #5
	//str w0, [x21, x1, lsl #2]					// x21[5] <- 6

	mov x0, x21
	mov w1, w19
	mov w2, w20
	bl ReadMatrix
	
	adr x0, NewLine1
	bl printf

	mov x0, x21
	mov w1, w19
	mov w2, w20
	bl WriteMatrix	


	mov x0, x21
	mov w1, w19
	mov w2, w20
	bl CountDifferentLines
	mov w1, w0
	adr x0, MessageCountLinesFormat1
	bl printf

	mov x0, x21
	mov w1, w19
	mov w2, w20
	bl CountDifferentRows
	mov w1, w0
	adr x0, MessageCountRowsFormat1
	bl printf

    ldr x21, [sp], #8
    ldr x20, [sp], #8
    ldr x19, [sp], #8
    ldr x30, [sp], #8

    mov x0, #0

    ret

MessageCountLinesFormat1:
	.asciz "Кол-во строк, все элементы которых различны: %d\n"
MessageCountRowsFormat1:
	.asciz "Кол-во столбцов, все элементы которых различны: %d\n"
NewLine1:
	.asciz "\n"

