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
	mov x0, #-12
	ret
	
	.global	CountDifferentRows
CountDifferentRows:
	mov x0, #-123
	ret
