    .text

    .globl CheckAllDifferent
CheckAllDifferent:
    push %ebp
    movl %esp, %ebp
    subl $20, %esp

    # Занятый стек 40 байт:
    #  16(%ebp) [4] size
    #  12(%ebp) [4] step
    #   8(%ebp) [4] pArray
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] 
    #  -4(%ebp) [4] 
    #  -5(%ebp) [1] result
    #  -6(%ebp) [1] 
    #  -7(%ebp) [1] 
    #  -8(%ebp) [1] 
    # -12(%ebp) [4] max = step * size
    # -16(%ebp) [4] i
    # -20(%ebp) [4] j

    # -12(%ebp) <- 16(%ebp) * 12(%ebp)
    movl 12(%ebp), %eax
    mull 16(%ebp)
    movl %eax, -12(%ebp)

    # for (-16(%ebp) <- 0; -16(%ebp) < -12(%ebp); -16(%ebp) += 12(%ebp))
    Loop1_Start:
        # -16(%ebp) <- 0
        movl $0, -16(%ebp)
        jmp Loop1_Check
        Loop1_Body:
            # for (-20(%ebp) <- -16(%ebp) + 12(%ebp); -20(%ebp) < -12(%ebp); -20(%ebp) += 12(%ebp))
            Loop2_Start:
                # -20(%ebp) <- -16(%ebp) + 12(%ebp)
                movl -16(%ebp), %eax
                addl 12(%ebp), %eax
                movl %eax, -20(%ebp)
                jmp Loop2_Check
                Loop2_Body:
                    # %eax <- 8(%ebp)[-16(%ebp)]
                    movl 8(%ebp), %eax
                    movl -16(%ebp), %ecx
                    movl (%eax,%ecx,4), %eax
                    # ;if %eax != 8(%ebp)[-20(%ebp)] goto Loop2_Continue
                    movl 8(%ebp), %ecx
                    movl -20(%ebp), %edx
                    cmpl (%ecx,%edx,4), %eax
                    jne Loop2_Continue
                    # -5(%ebp) <- $0
                    movb $0, -5(%ebp)
                    jmp Return1
                    Loop2_Continue:
                        # -20(%ebp) += 12(%ebp)
                        movl 12(%ebp), %eax
                        addl %eax, -20(%ebp)
                Loop2_Check:
                    # ;if -20(%ebp) < -12(%ebp) goto Loop2_Body
                    movl -20(%ebp), %eax
                    cmpl -12(%ebp), %eax
                    jl Loop2_Body
                # -16(%ebp) += 12(%ebp)
                movl 12(%ebp), %eax
                addl %eax, -16(%ebp)
        Loop1_Check:
            # ;if -16(%ebp) < -12(%ebp) goto Loop1_Body
            movl -16(%ebp), %eax
            cmpl -12(%ebp), %eax
            jl Loop1_Body

    # -5(%ebp) <- $1
    movb $1, -5(%ebp)

    Return1:
    # %al <- -5(%ebp)
    movb -5(%ebp), %al
    
    addl $20, %esp
    pop %ebp
    ret


    .globl CountDifferentLines
CountDifferentLines:
    pushl %ebp
    movl %esp, %ebp
    subl $24, %esp

    # Занятый стек 44 байт:
    #  16(%ebp) [4] n
    #  12(%ebp) [4] m
    #   8(%ebp) [4] pMatrix
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] 
    #  -4(%ebp) [4] c
    #  -8(%ebp) [4] i
    #  -9(%ebp) [1] check
    # -10(%ebp) [1] 
    # -11(%ebp) [1] 
    # -12(%ebp) [1] 
    # -16(%ebp) [4] 8(%esp) n
    # -20(%ebp) [4] 4(%esp) 1
    # -24(%ebp) [4] 0(%esp) pMatrix + i * n

    # -4(%ebp) <- 0
    movl $0, -4(%ebp)

    # for (-8(%ebp) <- 0; -8(%ebp) < 12(%ebp); -8(%ebp)++)
    Loop3_Start:
        # -8(%ebp) <- 0
        movl $0, -8(%ebp)
        jmp Loop3_Check
        Loop3_Body:
            movl 8(%ebp), %eax
            movl -8(%ebp), %ecx
            imull 16(%ebp), %ecx
            imull $4, %ecx
            addl %ecx, %eax
            movl 16(%ebp), %ecx
            movl %eax, (%esp)
            movl $1, 4(%esp)
            movl %ecx, 8(%esp)
            calll CheckAllDifferent
            andb $1, %al
            movb %al, -9(%ebp)
            testb $1, -9(%ebp)
            je Loop3_Continue
            movl -4(%ebp), %eax
            addl $1, %eax
            movl %eax, -4(%ebp)
            Loop3_Continue:
                movl -8(%ebp), %eax
                addl $1, %eax
                movl %eax, -8(%ebp)
        Loop3_Check:
            movl -8(%ebp), %eax
            cmpl 12(%ebp), %eax
            jl Loop3_Body
    
    # %eax <- -4(%ebp)
    movl -4(%ebp), %eax

    addl $24, %esp
    popl %ebp
    retl


    .globl CountDifferentRows
CountDifferentRows:
    pushl %ebp
    movl %esp, %ebp
    subl $24, %esp

    # Занятый стек 44 байт:
    #  16(%ebp) [4] n
    #  12(%ebp) [4] m
    #   8(%ebp) [4] pMatrix
    #   4(%ebp) [4] old %ebp
    #   0(%ebp) [4] 
    #  -4(%ebp) [4] c
    #  -8(%ebp) [4] i
    #  -9(%ebp) [1] check
    # -10(%ebp) [1] 
    # -11(%ebp) [1] 
    # -12(%ebp) [1] 
    # -16(%ebp) [4] 8(%esp) m
    # -20(%ebp) [4] 4(%esp) n
    # -24(%ebp) [4] 0(%esp) pMatrix + i

    # -4(%ebp) <- 0
    movl $0, -4(%ebp)

    Loop4_Start:
        movl $0, -8(%ebp)
        jmp Loop4_Check
        Loop4_Body:
            movl 8(%ebp), %eax
            movl -8(%ebp), %ecx
            imull $4, %ecx
            addl %ecx, %eax
            movl 16(%ebp), %ecx
            movl 12(%ebp), %edx
            movl %eax, (%esp)
            movl %ecx, 4(%esp)
            movl %edx, 8(%esp)
            calll CheckAllDifferent
            andb $1, %al
            movb %al, -9(%ebp)
            testb $1, -9(%ebp)
            je Loop4_Continue
            movl -4(%ebp), %eax
            addl $1, %eax
            movl %eax, -4(%ebp)
            Loop4_Continue:
                movl -8(%ebp), %eax
                addl $1, %eax
                movl %eax, -8(%ebp)
        Loop4_Check:
            movl -8(%ebp), %eax
            cmpl 16(%ebp), %eax
            jl Loop4_Body

    # %eax <- -4(%ebp)
    movl -4(%ebp), %eax

    addl $24, %esp
    popl %ebp
    retl
