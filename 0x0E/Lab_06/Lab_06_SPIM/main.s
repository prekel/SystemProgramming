    .text

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

    move $s0, $a0
    move $s1, $a1
    move $s2, $a2

    #li $v0, 1
    #lw $a0, ($a0)
    #move $a0, $a1
    #syscall	

    Loop1_Start:
        li $s3, 0
        j  Loop1_Check
        Loop1_Body:
            Loop2_Start:
            li $s4, 0
            j Loop2_Check
            Loop2_Body:

                li $v0, 1
                mul $t1, $s3, $s2
                add $t1, $t1, $s4
                li $t0, 4
                mul $t1, $t1, $t0
                add $t0, $s0, $t1
                lw $a0, ($t0)
                syscall

                li $v0, 4
                la $a0, Space1
                syscall

                Loop2_Continue:
                    addi $s4, $s4, 1
                Loop2_Check:
                    blt $s4, $s2, Loop2_Body
            li $v0, 4
            la $a0, NewLine1
            syscall
            addi $s3, $s3, 1
        Loop1_Check:
            blt $s3, $s1, Loop1_Body

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


    .globl	main
main:

    addi $sp, $sp, -24
    li $t0, 132
    sw $t0, ($sp)
    addi $sp, $sp, 4
    li $t0, 243
    sw $t0, ($sp)
    addi $sp, $sp, 4
    li $t0, 346
    sw $t0, ($sp)
    addi $sp, $sp, 4
    li $t0, -44
    sw $t0, ($sp)
    addi $sp, $sp, 4
    li $t0, 5
    sw $t0, ($sp)
    addi $sp, $sp, 4
    li $t0, 6
    sw $t0, ($sp)
    addi $sp, $sp, 4
    addi $sp, $sp, -24

    move $a0, $sp 
    li $a1, 3
    li $a2, 2
    jal WriteMatrix

    li	$v0,10		# exit
    syscall

    
    .data
Space1:	
    .asciiz	" "
NewLine1:
    .asciiz "\n"
