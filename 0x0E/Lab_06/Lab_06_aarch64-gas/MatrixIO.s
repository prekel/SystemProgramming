    .text

// void ReadMN(int* pM, int* pN)
    .global ReadMN
ReadMN:
    stp x19, x30, [sp, #-16]!
    stp xzr, x20, [sp, #-16]!

    mov x19, x0                                 // x19 <- x0
    mov x20, x1                                 // x20 <- x1 

    adr x0, InputMNMessage1                     // x0 <- &InputMNMessage1
    bl printf                                   // call printf

    adr x0, InputMNFormat1                      // x0 <- &InputMNFormat1
    mov x1, x19                                 // x1 <- x19 
    mov x2, x20                                 // x2 <- x20
    bl scanf                                    // call scanf

    ldp xzr, x20, [sp], #16
    ldp x19, x30, [sp], #16
    ret


// void ReadMatrix(int* pMatrix, int m, int n)
    .global ReadMatrix
ReadMatrix:
    stp x19, x30, [sp, #-16]!
    stp x21, x20, [sp, #-16]!
    stp x23, x22, [sp, #-16]!

    mov x19, x0                                 // x19 <- x0
    mov w20, w1                                 // w20 <- w1
    mov w21, w2                                 // w21 <- w2

    // for (w22 <- 0, w22 < x20, w22++)
    Loop3_Start:
        mov w22, #0                             // w22 <- 0
        b Loop3_Check                           // goto Loop3_Check
        Loop3_Body:
            // for (w23 <- 0, w23 < x21, w23++)
            Loop4_Start:
                mov w23, #0                     // w23 <- 0
                b Loop4_Check                   // goto Loop4_Check
                Loop4_Body:
                    adr x0, InputMessageFormat1 // x0 <- &InputMessageFormat1
                    mov w1, w22                 // w1 <- w22
                    mov w2, w23                 // w2 <- w23
                    bl printf                   // call printf
                    adr x0, InputFormat1        // x0 <- &InputFormat1
                    madd w1, w22, w21, w23      // w1 <- w22 * w21 + w23
                    mov w2, #4                  // w2 <- 4
                    mul w1, w1, w2              // w1 *= w2
                    add x1, x19, x1             // x1 += x19
                    bl scanf                    // call scanf
                    add w23, w23, #1            // w23++
                Loop4_Check:
                    cmp w23, w21                //  if w23 < w21
                    b.lt Loop4_Body             //  goto Loop4_Body
            add w22, w22, #1                    // w22++
        Loop3_Check:
            cmp w22, w20                        //  if w22 < w20
            b.lt Loop3_Body                     //  goto Loop3_Body

    ldp x23, x22, [sp], #16
    ldp x21, x20, [sp], #16
    ldp x19, x30, [sp], #16
    ret


// void WriteMatrix(int* pMatrix, int m, int n)
    .global WriteMatrix
WriteMatrix:
    stp x19, x30, [sp, #-16]!
    stp x21, x20, [sp, #-16]!
    stp x23, x22, [sp, #-16]!

    mov x19, x0                                 // x19 <- x0
    mov w20, w1                                 // w20 <- w1
    mov w21, w2                                 // w21 <- w2

    adr x0, OutputFormatMatrix1                 // x0 <- &OutputFormatMatrix1
    bl printf                                   // call printf

    // for (w22 <- 0, w22 < x20, w22++)
    Loop1_Start:
        mov w22, #0                             // w22 <- 0
        b Loop1_Check                           // goto Loop1_Check
        Loop1_Body:
            // for (w23 <- 0, w23 < x21, w23++)
            Loop2_Start:
                mov w23, #0                     // w23 <- 0
                b Loop2_Check                   // goto Loop2_Check
                Loop2_Body:
                    adr x0, OutputFormat1       // x0 <- &OutputFormat1
                    madd w1, w22, w21, w23      // w1 <- w22 * w21 + w23
                    ldr w1, [x19, x1, lsl#2]    // w1 <- x19[x1]
                    bl printf                   // call printf
                    add w23, w23, #1            // w23++
                Loop2_Check:
                    cmp w23, w21                //  if w23 < w21
                    b.lt Loop2_Body             //  goto Loop2_Body
            adr x0, NewLine                     // x0 <- &NewLine
            bl printf                           // call printf
            add w22, w22, #1                    // w22++
        Loop1_Check:
            cmp w22, w20                        //  if w22 < w20
            b.lt Loop1_Body                     //  goto Loop1_Body

    ldp x23, x22, [sp], #16
    ldp x21, x20, [sp], #16
    ldp x19, x30, [sp], #16
    ret 


OutputFormatMatrix1:
    .asciz "Матрица a[%d][%d]:\n"

OutputFormat1:
    .asciz "%d "

NewLine:
    .asciz "\n"

InputMessageFormat1:
    .asciz "Введите a[%d][%d]: "

InputFormat1:
    .asciz "%d"

InputMNMessage1:
    .asciz "Введите M и N (кол-во строк и столбцов, a[M][N]): "

InputMNFormat1:
    .asciz "%d%d"
