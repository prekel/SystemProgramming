# Вариант 4. 
# Дана целочисленная матрица размера M x N. 
# Найти количество ее строк и столбцов, все элементы которых различны.
    .text

# bool CheckAllDifferent(int* pArray, int step, int size)
    .globl CheckAllDifferent
CheckAllDifferent:
    mul $t3, $a1, $a2                           # $t3 <- $a1 * $a2

    Loop5_Start:
        li $t4, 0                               # $t4 <- 0
        j Loop5_Check                           # goto Loop5_Check
        Loop5_Body:
            Loop6_Start:
                add $t5, $t4, $a1               # $t5 <- $t4 + $a1
                j Loop6_Check                   # goto Loop6_Check
                Loop6_Body:
                    li $t6, 4                   # $t6 <- 4
                    mul $t6, $t6, $t4           # $t6 *= $t4
                    add $t6, $t6, $a0           # $t6 += $a0
                    lw $t6, ($t6)               # $t6 <- *t6
                    li $t7, 4                   # $t7 <- 4
                    mul $t7, $t7, $t5           # $t7 *= $t5
                    add $t7, $t7, $a0           # $t7 += $a0
                    lw $t7, ($t7)               # $t7 <- *t7
                    bne $t6, $t7, Loop6_Cont    # if $t6 != $t7 goto Loop6_Cont
                    li $v0, 0                   # return false
                    jr $ra                      # go back to $ra
                    Loop6_Cont:
                        add $t5, $t5, $a1       # $t5 += $a1
                Loop6_Check:
                    blt $t5, $t3, Loop6_Body    # if $t5 < $t3 goto Loop6_Body
                add $t4, $t4, $a1               # $t4 += $a1
        Loop5_Check:
            blt $t4, $t3, Loop5_Body            # if $t4 < $t3 goto Loop5_Body

    li $v0, 1                                   # return true
    jr $ra                                      # go back to $ra


# int CountDifferentLines(int* pMatrix, int m, int n)
    .globl CountDifferentLines
CountDifferentLines:
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
    addi $sp, $sp, -4        
    sw $s5, ($sp)

    move $s0, $a0                               # $s0 <- $a0
    move $s1, $a1                               # $s1 <- $a1
    move $s2, $a2                               # $s2 <- w2

    li $s3, 0                                   # $s3 <- 0

    li $s5, 0                                   # $s5 <- 0

    # for ($s4 = 0, $s4 < $s1, $s4++)
    Loop7_Start:
        li $s4, 0                               # $s4 <- 0
        j Loop7_Check                           # goto Loop7_Check
        Loop7_Body:
            li $a0, 4                           # $a0 <- 4
            mul $a0, $a0, $s3                   # $a0 <- $s3 * 4
            add $a0, $a0, $s0                   # $a0 += $s0 
            li $a1, 1                           # $a1 <- 1
            move $a2, $s2                       # $a2 <- $s2
            jal CheckAllDifferent               # call CheckAllDifferent
            beq $v0, $zero, Loop7_Continue      # if $a0 == false goto Loop7_Continue
            add $s5, $s5, 1                     # $s5++
            Loop7_Continue:
                add $s3, $s3, $s2               # $s3 += $s2
                add $s4, $s4, 1                 # $s4++
        Loop7_Check:
            blt $s4, $s1, Loop7_Body            # if $s4 < $s1 goto Loop7_Body

    move $v0, $s5                               # return $s5

    lw $s5, ($sp)        
    addi $sp, $sp, 4
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
    jr $ra                                      # go back to $ra


# int CountDifferentRows(int* pMatrix, int m, int n)
    .globl CountDifferentRows
CountDifferentRows:
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
    addi $sp, $sp, -4        
    sw $s5, ($sp)

    move $s0, $a0                               # $s0 <- $a0
    move $s1, $a1                               # $s1 <- $a1
    move $s2, $a2                               # $s2 <- w2

    li $s5, 0                                   # $s5 <- 0

    # for ($s4 = 0, $s4 < $s2, $s4++)
    Loop8_Start:
        li $s4, 0                               # $s4 <- 0
        j Loop8_Check                           # goto Loop8_Check
        Loop8_Body:
            li $a0, 4                           # $a0 <- 4
            mul $a0, $a0, $s4                   # $a0 <- $s4 * 4
            add $a0, $a0, $s0                   # $a0 += $s0 
            move $a1, $s2                       # $a1 <- $s2
            move $a2, $s1                       # $a2 <- $s1
            jal CheckAllDifferent               # call CheckAllDifferent
            beq $v0, $zero, Loop8_Continue      # if $a0 == false goto Loop8_Continue
            add $s5, $s5, 1                     # $s5++
            Loop8_Continue:
                add $s4, $s4, 1                 # $s4++
        Loop8_Check:
            blt $s4, $s2, Loop8_Body            # if $s4 < $s2 goto Loop8_Body

    move $v0, $s5                               # $a0 <- $s5

    lw $s5, ($sp)        
    addi $sp, $sp, 4
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
    jr $ra                                      # go back to $ra


# void ReadMN(int* pM, int* pN)
    .globl ReadMN
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


    move $s0, $a0                               # $s0 <- $a0
    move $s1, $a1                               # $s1 <- $a1

    li $v0, 4                                   # $v0 <- 4
    la $a0, InputMNMessage1                     # $a0 <- &InputMNMessage1
    syscall                                     # syscall print_string

    li $v0, 5                                   # $v0 <- 5
    syscall                                     # syscall read_int

    sw $v0, ($s0)                               # *$s0 <- $v0

    li $v0, 5                                   # $v0 <- 5
    syscall                                     # syscall read_int

    sw $v0, ($s1)                               # *$s1 <- $v0

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

    jr $ra                                      # go back to $ra  


# void ReadMatrix(int* pMatrix, int m, int n)
    .globl ReadMatrix
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


# void WriteMatrix(int* pMatrix, int m, int n)
    .globl WriteMatrix
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

    jr $ra                                      # go back to $ra


# int main()
    .globl main
main:
    move $a0, $sp                               # $a0 <- $sp
    addi $sp, $sp, -4                           # $sp -= 4
    move $a1, $sp                               # $a1 <- $sp
    jal ReadMN                                  # call ReadMN

    lw $s1, ($sp)                               # $s1 <- *$sp
    addi $sp, $sp, 4                            # $sp += 4
    lw $s0, ($sp)                               # $s0 <- *$sp

    li $t0, 4                                   # $t0 <- 4
    mul $t0, $t0, $s0                           # $t0 *= $s0
    mul $t0, $t0, $s1                           # $t0 *= $s1
    
    sub $sp, $sp, $t0                           # $sp += $t0

    move $a0, $sp                               # $a0 <- $sp
    move $a1, $s0                               # $a1 <- $s0
    move $a2, $s1                               # $a2 <- $s1
    jal ReadMatrix                              # call ReadMatrix

    li $v0, 4                                   # $v0 <- 4
    la $a0, NewLine1                            # $a0 <- &NewLine1
    syscall                                     # syscall print_string

    move $a0, $sp                               # $a0 <- $sp
    move $a1, $s0                               # $a1 <- $s0
    move $a2, $s1                               # $a2 <- $s1
    jal WriteMatrix                             # call WriteMatrix

    li $v0, 4                                   # $v0 <- 4
    la $a0, MessageCountLinesFormat1            # $a0 <- &MessageCountLinesFormat1
    syscall                                     # syscall print_string
    move $a0, $sp                               # $a0 <- $sp
    move $a1, $s0                               # $a1 <- $s0
    move $a2, $s1                               # $a2 <- $s1
    jal CountDifferentLines                     # call CountDifferentLines
    move $a0, $v0                               # $a0 <- $v0
    li $v0, 1                                   # $v0 <- 1
    syscall                                     # syscall print_int
    li $v0, 4                                   # $v0 <- 4
    la $a0, NewLine1                            # $a0 <- &NewLine1
    syscall                                     # syscall print_string
    
    li $v0, 4                                   # $v0 <- 4
    la $a0, MessageCountRowsFormat1             # $a0 <- &MessageCountRowsFormat1
    syscall                                     # syscall print_string
    move $a0, $sp                               # $a0 <- $sp
    move $a1, $s0                               # $a1 <- $s0
    move $a2, $s1                               # $a2 <- $s1
    jal CountDifferentRows                      # call CountDifferentRows
    move $a0, $v0                               # $a0 <- $v0
    li $v0, 1                                   # $v0 <- 1
    syscall                                     # syscall print_int
    li $v0, 4                                   # $v0 <- 4
    la $a0, NewLine1                            # $a0 <- &NewLine1
    syscall                                     # syscall print_string

    li $v0, 10                                  # $v0 <- 10
    syscall                                     # syscall exit


    .data
    
Space1:    
    .asciiz " "

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

MessageCountLinesFormat1:
    .asciiz "Кол-во строк, все элементы которых различны: "
    
MessageCountRowsFormat1:
    .asciiz "Кол-во столбцов, все элементы которых различны: "
