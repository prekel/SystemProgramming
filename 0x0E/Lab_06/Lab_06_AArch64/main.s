	.text

    .global	main
main:
    str x30, [sp, #-16]!
    str x19, [sp, #-16]!
    str x20, [sp, #-16]!
    str x21, [sp, #-16]!
	
	sub sp, sp, #8 								// добавление места в стеке для двух 4-байтных числа
	mov x0, sp									// x1 <- указатель на последнее число в стеке
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

	mov x0, x21
	bl free

    ldr x21, [sp], #16
    ldr x20, [sp], #16
    ldr x19, [sp], #16
    ldr x30, [sp], #16

    mov x0, #0

    ret

MessageCountLinesFormat1:
	.asciz "Кол-во строк, все элементы которых различны: %d\n"
MessageCountRowsFormat1:
	.asciz "Кол-во столбцов, все элементы которых различны: %d\n"
NewLine1:
	.asciz "\n"

