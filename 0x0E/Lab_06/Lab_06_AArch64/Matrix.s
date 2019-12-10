.text

	.global	CheckAllDifferent
CheckAllDifferent:
	mul x3, x1, x2 // x3 = x1 * x2

	Loop1_Start:
		mov x4, #0
		b Loop1_Check
		Loop1_Body:
			Loop2_Start:
				add x5, x4, x1
				b Loop2_Check
				Loop2_Body:
					add x5, x5, x1 // x5++
					ldr x6, [x0, x4] 
					ldr x7, [x0, x5]
					cmp x6, x7 // x6 == x7
					b.ne Loop2_Continue
						mov x0, #1
						ret
					Loop2_Continue:
				Loop2_Check:
					cmp x5, x3
					b.lt Loop2_Body
				add x4, x4, x1
		Loop1_Check:
			cmp x4, x3
			b.lt Loop1_Body

	mov x0, #0
	ret


	.global	CountDifferentLines
CountDifferentLines:
	mov x0, #-12
	ret
	
	.global	CountDifferentRows
CountDifferentRows:
	mov x0, #-123
	ret
