    .text

    .globl	CheckAllDifferent
CheckAllDifferent:
    pushl	%ebp
    movl	%esp, %ebp
    pushl	%esi
    subl	$16, %esp

    # movl	16(%ebp), %eax
    # movl	12(%ebp), %ecx
    # movl	8(%ebp), %edx

	# -12(%ebp) <- 16(%ebp) * 12(%ebp)
    movl 12(%ebp), %eax
	mull 16(%ebp)
    movl %eax, -12(%ebp)

	Loop1_Start:
		# -16(%ebp) <- 0
    	movl $0, -16(%ebp)
		jmp Loop1_Check
        Loop1_Body:
            Loop2_Start:
				# -20(%ebp) <- -16(%ebp) + 12(%ebp)
    			movl -16(%ebp), %eax
    			addl 12(%ebp), %eax
    			movl %eax, -20(%ebp)
                Loop2_Body:
    				movl 8(%ebp), %eax
    				movl -16(%ebp), %ecx
    				movl (%eax,%ecx,4), %eax
    				movl 8(%ebp), %ecx
    				movl -20(%ebp), %edx
    				cmpl (%ecx,%edx,4), %eax
					jne Loop2_Continue
    				movb $0, -5(%ebp)
                    Loop2_Continue:
						# -20(%ebp) += 12(%ebp)
						movl 12(%ebp), %eax
    					addl -20(%ebp), %eax
    					movl %eax, -20(%ebp)
                Loop2_Check:
					movl -20(%ebp), %eax
    				cmpl -12(%ebp), %eax
					jl Loop2_Body
				movl	12(%ebp), %eax
    			addl	-16(%ebp), %eax
    			movl	%eax, -16(%ebp)
        Loop1_Check:
			movl	-16(%ebp), %eax
    		cmpl	-12(%ebp), %eax
			jl Loop1_Body



; 	# -16(%ebp) <- 0
;     movl	$0, -16(%ebp)

; .LBB0_1:
;     movl	-16(%ebp), %eax
;     cmpl	-12(%ebp), %eax
;     jge	.LBB0_10
;     movl	-16(%ebp), %eax
;     addl	12(%ebp), %eax
;     movl	%eax, -20(%ebp)
; .LBB0_3:
;     movl	-20(%ebp), %eax
;     cmpl	-12(%ebp), %eax
;     jge	.LBB0_8
;     movl	8(%ebp), %eax
;     movl	-16(%ebp), %ecx
;     movl	(%eax,%ecx,4), %eax
;     movl	8(%ebp), %ecx
;     movl	-20(%ebp), %edx
;     cmpl	(%ecx,%edx,4), %eax
;     jne	.LBB0_6
;     movb	$0, -5(%ebp)
;     jmp	.LBB0_11
; .LBB0_6:
;     jmp	.LBB0_7
; .LBB0_7:
;     movl	12(%ebp), %eax
;     addl	-20(%ebp), %eax
;     movl	%eax, -20(%ebp)
;     jmp	.LBB0_3
; .LBB0_8:
;     jmp	.LBB0_9
; .LBB0_9:
;     movl	12(%ebp), %eax
;     addl	-16(%ebp), %eax
;     movl	%eax, -16(%ebp)
;     jmp	.LBB0_1
; .LBB0_10:
;     movb	$1, -5(%ebp)
; .LBB0_11:

	Return1:
    movb	-5(%ebp), %al
    # andb	$1, %al
    # movzbl	%al, %eax
    addl	$16, %esp
    pop	%esi
    pop	%ebp
    ret


    .globl	CountDifferentLines
CountDifferentLines:
    pushl	%ebp
    movl	%esp, %ebp
    subl	$24, %esp
    movl	16(%ebp), %eax
    movl	12(%ebp), %ecx
    movl	8(%ebp), %edx
    movl	$0, -4(%ebp)
    movl	$0, -8(%ebp)
.LBB1_1:
    movl	-8(%ebp), %eax
    cmpl	12(%ebp), %eax
    jge	.LBB1_6
    movl	8(%ebp), %eax
    movl	-8(%ebp), %ecx
    imull	16(%ebp), %ecx
    shll	$2, %ecx
    addl	%ecx, %eax
    movl	16(%ebp), %ecx
    movl	%eax, (%esp)
    movl	$1, 4(%esp)
    movl	%ecx, 8(%esp)
    calll	CheckAllDifferent
    andb	$1, %al
    movb	%al, -9(%ebp)
    testb	$1, -9(%ebp)
    je	.LBB1_4
    movl	-4(%ebp), %eax
    addl	$1, %eax
    movl	%eax, -4(%ebp)
.LBB1_4:
    jmp	.LBB1_5
.LBB1_5:
    movl	-8(%ebp), %eax
    addl	$1, %eax
    movl	%eax, -8(%ebp)
    jmp	.LBB1_1
.LBB1_6:
    movl	-4(%ebp), %eax
    addl	$24, %esp
    popl	%ebp
    retl


    .globl	CountDifferentRows
CountDifferentRows:
    pushl	%ebp
    movl	%esp, %ebp
    subl	$24, %esp
    movl	16(%ebp), %eax
    movl	12(%ebp), %ecx
    movl	8(%ebp), %edx
    movl	$0, -4(%ebp)
    movl	$0, -8(%ebp)
.LBB2_1:
    movl	-8(%ebp), %eax
    cmpl	16(%ebp), %eax
    jge	.LBB2_6
    movl	8(%ebp), %eax
    movl	-8(%ebp), %ecx
    shll	$2, %ecx
    addl	%ecx, %eax
    movl	16(%ebp), %ecx
    movl	12(%ebp), %edx
    movl	%eax, (%esp)
    movl	%ecx, 4(%esp)
    movl	%edx, 8(%esp)
    calll	CheckAllDifferent
    andb	$1, %al
    movb	%al, -9(%ebp)
    testb	$1, -9(%ebp)
    je	.LBB2_4
    movl	-4(%ebp), %eax
    addl	$1, %eax
    movl	%eax, -4(%ebp)
.LBB2_4:
    jmp	.LBB2_5
.LBB2_5:
    movl	-8(%ebp), %eax
    addl	$1, %eax
    movl	%eax, -8(%ebp)
    jmp	.LBB2_1
.LBB2_6:
    movl	-4(%ebp), %eax
    addl	$24, %esp
    popl	%ebp
    retl
