.text

	.global	CheckAllDifferent
CheckAllDifferent:
	mul w3, w1, w2                              // w3 <- w1 * w2

	Loop1_Start:
		mov w4, #0                              // w4 <- 0
		b Loop1_Check                           // goto Loop1_Check
		Loop1_Body:
			Loop2_Start:
				add w5, w4, w1                  // w5 <- w4 + w1
				b Loop2_Check
				Loop2_Body:
					ldr w6, [x0, x4, lsl #2]    // w6 <- x0[x4]
					ldr w7, [x0, x5, lsl #2]    // w7 <- x0[x5]
					cmp w6, w7                  //  if w6 != w7
					b.ne Loop2_Continue         //  goto Loop2_Continue
						mov w0, #0              // return false
						ret
					Loop2_Continue:
					    add w5, w5, w1          // w5 += w1
				Loop2_Check:
					cmp w5, w3                  //  if w5 < w3
					b.lt Loop2_Body             //  goto Loop2_Body
				add w4, w4, w1                  // w4 += w1
		Loop1_Check:
			cmp w4, w3                          //  if w4 < w3
			b.lt Loop1_Body                     //  goto Loop1_Body

	mov w0, #1                                  // return true
	ret


	.global	CountDifferentLines
CountDifferentLines:
    str x30, [sp, #-8]!
    str x19, [sp, #-8]!
    str x20, [sp, #-8]!
    str x23, [sp, #-8]!
    str x24, [sp, #-8]!
    str x25, [sp, #-8]!

    mov x23, x0                                 // x23 <- x0
    mov x24, x1                                 // x24 <- x1
    mov x25, x2                                 // x25 <- x2

    mov w19, #0                                 // x19 <- 0

    // for (x20 = 0, x20 < x24, x20++)
    Loop3_Start:
        mov x20, #0                             // x20 <- 0
        b Loop3_Check                           // goto Loop3_Check
        Loop3_Body:
            madd x0, x20, x25, x23              // x0 <- x20 * x25 + x23
            mov x1, #1                          // x1 <- 1
            mov x2, x25                         // x2 <- x25
            bl CheckAllDifferent                // call CheckAllDifferent
            cmp x0, #0                          //  if x0 == false
            b.eq Loop3_Continue                 //  goto Loop3_Continue
            add w19, w19, #1                    // w19++

            adr x0, DecimalIntDebugFormat
            mov w1, x20
            bl printf

            Loop3_Continue:
                add x20, x20, #1                // x20++
        Loop3_Check:
            cmp x20, x24                        //  if x20 < x24
            b.lt Loop3_Body                     //  goto Loop3_Body

	mov w0, w19

    ldr x25, [sp], #8
    ldr x24, [sp], #8
    ldr x23, [sp], #8
    ldr x20, [sp], #8
    ldr x19, [sp], #8
    ldr x30, [sp], #8

	ret
	
	.global	CountDifferentRows
CountDifferentRows:
	str x30, [sp, #-8]!
    str x19, [sp, #-8]!
    str x20, [sp, #-8]!
    str x23, [sp, #-8]!
    str x24, [sp, #-8]!
    str x25, [sp, #-8]!

    mov x23, x0                                 // x23 <- x0
    mov x24, x1                                 // x24 <- x1
    mov x25, x2                                 // x25 <- x2

    mov w19, #0                                 // x19 <- 0

    // for (x20 = 0, x20 < x25, x20++)
    Loop4_Start:
        mov x20, #0                             // x20 <- 0
        b Loop4_Check                           // goto Loop4_Check
        Loop4_Body:
            add x0, x20, x23                    // x0 <- x20 + x23
            mov x1, x25                         // x1 <- x25
            mov x2, x24                         // x2 <- x24
            bl CheckAllDifferent                // call CheckAllDifferent
            cmp x0, #0                          //  if x0 == false
            b.eq Loop4_Continue                 //  goto Loop4_Continue
            add w19, w19, #1                    // w19++
            Loop4_Continue:
                add x20, x20, #1                // x20++
        Loop4_Check:
            cmp x20, x25                        //  if x20 < x25
            b.lt Loop4_Body                     //  goto Loop4_Body

	mov w0, w19

    ldr x25, [sp], #8
    ldr x24, [sp], #8
    ldr x23, [sp], #8
    ldr x20, [sp], #8
    ldr x19, [sp], #8
    ldr x30, [sp], #8

	ret

DecimalIntDebugFormat:
    .asciz "|-%d--"
