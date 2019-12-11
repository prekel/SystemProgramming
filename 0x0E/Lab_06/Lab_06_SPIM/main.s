    .text

    .globl	ReadMN
ReadMN:
    addi $sp, $sp, -4		
    sw $ra, ($sp)		
    addi $sp, $sp, -4		
    sw $s0, ($sp)	
    addi $sp, $sp, -4		
    sw $s1, ($sp)	
    addi $sp, $sp, -4		
    sw $s2, ($sp)	
    addi $sp, $sp, -4		
    sw $s3, ($sp)	
    addi $sp, $sp, -4		
    sw $s4, ($sp)


    move $s0, $a0
    move $s1, $a1

    li $v0, 4
    la $a0, InputMNMessage1
    syscall

    li $v0, 5
    syscall

    sw $v0, ($s0)

    li $v0, 5
    syscall

    sw $v0, ($s1)

	lw $s4, ($sp)		
	addi $sp, $sp, 4	
	lw $s3, ($sp)		
	addi $sp, $sp, 4	
	lw $s2, ($sp)		
	addi $sp, $sp, 4	
	lw $s1, ($sp)		
	addi $sp, $sp, 4	
	lw $s0, ($sp)		
	addi $sp, $sp, 4	
	lw $ra, ($sp)		
	addi $sp, $sp, 4		

    jr $ra           


    .globl	ReadMatrix
ReadMatrix:
    addi $sp, $sp, -4		
    sw $ra, ($sp)		
    addi $sp, $sp, -4		
    sw $s0, ($sp)	
    addi $sp, $sp, -4		
    sw $s1, ($sp)	
    addi $sp, $sp, -4		
    sw $s2, ($sp)	
    addi $sp, $sp, -4		
    sw $s3, ($sp)	
    addi $sp, $sp, -4		
    sw $s4, ($sp)


    move $s0, $a0                               # $s0 <- $a0
    move $s1, $a1                               # $s1 <- $a1
    move $s2, $a2                               # $s2 <- $a2

    # for ($s3 <- 0; $s3 < $s1; $s3++)
    Loop3_Start:
        li $s3, 0                               # $s3 <- 0
        j  Loop3_Check                          # goto Loop3_Check
        Loop3_Body:
            # for ($s4 <- 0; $s4 < $s2; $s4++)
            Loop4_Start:
                li $s4, 0                       # $s4 <- 0
                j Loop4_Check                   # goto Loop4_Check
                Loop4_Body:

                    li $v0, 4
                    la $a0, InputMessagePart1
                    syscall
                    li $v0, 1
                    move $a0, $s3
                    syscall
                    li $v0, 4
                    la $a0, InputMessagePart2
                    syscall
                    li $v0, 1
                    move $a0, $s4
                    syscall
                    li $v0, 4
                    la $a0, InputMessagePart3
                    syscall

                    li $v0, 5                   # $v0 <- 5
                    syscall                     # syscall read_int
                    move $t3, $v0

                    mul $t0, $s3, $s2           # $t0 <- $s3 * $s2
                    add $t0, $t0, $s4           # t0 += $s4
                    li $t1, 4                   # $t1 <- 4
                    mul $t0, $t0, $t1           # $t0 *= 4
                    add $t0, $t0, $s0           # $t0 += $s0 
                    sw $t3, ($t0)               # *t0 <- $a0

                    addi $s4, $s4, 1            # $s4++
                    Loop4_Check:
                       blt $s4, $s2, Loop4_Body # if $s4 < $s2 goto Loop4_Body
            addi $s3, $s3, 1                    # $s3++
        Loop3_Check:
            blt $s3, $s1, Loop3_Body            # if $s3 < $s1 goto Loop3_Body


	lw $s4, ($sp)		
	addi $sp, $sp, 4	
	lw $s3, ($sp)		
	addi $sp, $sp, 4	
	lw $s2, ($sp)		
	addi $sp, $sp, 4	
	lw $s1, ($sp)		
	addi $sp, $sp, 4	
	lw $s0, ($sp)		
	addi $sp, $sp, 4	
	lw $ra, ($sp)		
	addi $sp, $sp, 4		

    jr $ra           


    .globl	WriteMatrix
WriteMatrix:
    addi $sp, $sp, -4		
    sw $ra, ($sp)		
    addi $sp, $sp, -4		
    sw $s0, ($sp)	
    addi $sp, $sp, -4		
    sw $s1, ($sp)	
    addi $sp, $sp, -4		
    sw $s2, ($sp)	
    addi $sp, $sp, -4		
    sw $s3, ($sp)	
    addi $sp, $sp, -4		
    sw $s4, ($sp)

    move $s0, $a0                               # $s0 <- $a0
    move $s1, $a1                               # $s1 <- $a1
    move $s2, $a2                               # $s2 <- $a2

    li $v0, 4
    la $a0, OutputFormatMatrixPart1
    syscall
    li $v0, 1
    move $a0, $s1
    syscall
    li $v0, 4
    la $a0, OutputFormatMatrixPart2
    syscall
    li $v0, 1
    move $a0, $s2
    syscall
    li $v0, 4
    la $a0, OutputFormatMatrixPart3
    syscall

    # for ($s3 <- 0; $s3 < $s1; $s3++)
    Loop1_Start:
        li $s3, 0                               # $s3 <- 0
        j  Loop1_Check                          # goto Loop1_Check
        Loop1_Body:
            # for ($s4 <- 0; $s4 < $s2; $s4++)
            Loop2_Start:
                li $s4, 0                       # $s4 <- 0
                j Loop2_Check                   # goto Loop2_Check
                Loop2_Body:
                    li $v0, 1                   # $v0 <- 1
                    mul $t1, $s3, $s2           # $t1 <- $s3 * $s2
                    add $t1, $t1, $s4           # $t1 += $s4
                    li $t0, 4                   # $t0 <- 4
                    mul $t1, $t1, $t0           # $t1 *= $t0
                    add $t0, $s0, $t1           # $t0 <- $s0 + $t1
                    lw $a0, ($t0)               # $a0 <- *t0
                    syscall                     # syscall print_int
                    li $v0, 4                   # $v0 <- 4
                    la $a0, Space1              # $a1 <- &Space1
                    syscall                     # syscall print_string
                    addi $s4, $s4, 1            # $s4++
                    Loop2_Check:
                       blt $s4, $s2, Loop2_Body # if $s4 < $s2 goto Loop2_Body
            li $v0, 4                           # $v0 <- 4
            la $a0, NewLine1                    # $a0 <- &NewLine1
            syscall                             # syscall print_string
            addi $s3, $s3, 1                    # $s3++
        Loop1_Check:
            blt $s3, $s1, Loop1_Body            # if $s3 < $s1 goto Loop1_Body

	lw $s4, ($sp)		
	addi $sp, $sp, 4	
	lw $s3, ($sp)		
	addi $sp, $sp, 4	
	lw $s2, ($sp)		
	addi $sp, $sp, 4	
	lw $s1, ($sp)		
	addi $sp, $sp, 4	
	lw $s0, ($sp)		
	addi $sp, $sp, 4	
	lw $ra, ($sp)		
	addi $sp, $sp, 4		

    jr $ra                                      # return


    .globl	main
main:

    move $a0, $sp
    addi $sp, $sp, -4
    move $a1, $sp
    jal ReadMN

    lw $s1, ($sp)
    addi $sp, $sp, 4
    lw $s0, ($sp) 

    li $t0, 4
    mul $t0, $t0, $s0 
    mul $t0, $t0, $s1
    
    sub $sp, $sp, $t0

    move $a0, $sp 
    move $a1, $s0
    move $a2, $s1
    jal ReadMatrix

    li $v0, 4
    la $a0, NewLine1
    syscall

    move $a0, $sp 
    move $a1, $s0
    move $a2, $s1
    jal WriteMatrix

    li	$v0, 10
    syscall


    .data
Space1:	
    .asciiz	" "
NewLine1:
    .asciiz "\n"

InputMessagePart1:
	.asciiz "Введите a["
InputMessagePart2:
	.asciiz "]["
InputMessagePart3:
	.asciiz "]: "

OutputFormatMatrixPart1:
    .asciiz "Матрица a["
OutputFormatMatrixPart2:
    .asciiz "]["
OutputFormatMatrixPart3:
    .asciiz "]:\n"

InputMNMessage1:
	.asciiz "Введите M и N (кол-во строк и столбцов, a[M][N]): "
