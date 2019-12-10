.text

	.global	ReadMN
ReadMN:
	mov x0, #4
	ret

	.global	ReadMatrix
ReadMatrix:
	mov x0, #5
	ret

	.global	WriteMatrix
WriteMatrix:
    str x30, [sp, #-8]!
    str x19, [sp, #-8]!
    str x20, [sp, #-8]!
    str x21, [sp, #-8]!
    str x22, [sp, #-8]!
    str x23, [sp, #-8]!

	mov x19, x0									// x19 <- x0 
	mov w20, w1									// w20 <- w1 
	mov w21, w2									// w21 <- w2 

	adr x0, OutputFormatMatrix1                 // x0 <- &OutputFormatMatrix1
	bl printf									// call printf

	// for (w22 <- 0, w22 < x20, w22++)
	Loop1_Start:
		mov w22, #0                             // w22 <- 0
		b Loop1_Check                           // goto Loop1_Check
		Loop1_Body:
			// for (w23 <- 0, w23 < x21, w23++)
			Loop2_Start:
				mov w23, #0                 	// w23 <- 0
				b Loop2_Check					// goto Loop2_Check
				Loop2_Body:
					adr x0, OutputFormat1		// x0 <- &OutputFormat1
					madd w1, w22, w21, w23 		// w1 <- w22 * w21 + w23 
					ldr w1, [x19, x1, lsl#2]	// w1 <- x19[x1]
					bl printf					// call printf 
					Loop2_Continue:
					    add w23, w23, #1        // w23++
				Loop2_Check:
					cmp w23, w21                //  if w23 < w21
					b.lt Loop2_Body             //  goto Loop2_Body
				add w23, w23, #1                // w23++
			adr x0, NewLine						// x0 <- &NewLine
			bl printf							// call printf
			add w22, w22, #1					// w22++
		Loop1_Check:
			cmp w22, w20                        //  if w22 < w20
			b.lt Loop1_Body 					//  goto Loop1_Body

    ldr x23, [sp], #8
    ldr x22, [sp], #8
	ldr x21, [sp], #8
    ldr x20, [sp], #8
    ldr x19, [sp], #8
    ldr x30, [sp], #8
	ret

OutputFormatMatrix1:
	.asciz "Матрица a[%d][%d]:\n"

OutputFormat1:
	.asciz "%d "

NewLine:
	.asciz "\n"
