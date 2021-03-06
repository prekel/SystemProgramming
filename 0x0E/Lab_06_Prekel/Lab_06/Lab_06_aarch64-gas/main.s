// Вариант 4. 
// Дана целочисленная матрица размера M x N. 
// Найти количество ее строк и столбцов, все элементы которых различны.
    .text

// int main()
    .global main
main:
    stp x19, x30, [sp, #-16]!
    stp x21, x20, [sp, #-16]!
    
    sub sp, sp, #16                             // добавление места в стеке для двух 4-байтных числа и выравнивание до 16 байт
    mov x20, sp                                 // x20 <- sp
    mov x1, x20                                 // x1 <- x20 
    add x20, x20, #4                            // x20 += 4
    mov x0, x20                                 // x0 <- x20 
    bl ReadMN                                   // call ReadMN
    ldr w19, [x20]                              // w19 <- *x20 
    sub x20, x20, #4                            // x20 -= 4
    ldr w21, [x20]                              // w21 = *x20 
    add sp, sp, #16                             // sp += 16
    mov w20, w21                                // w20 <- w21 

    mul w0, w19, w20                            // w0 <- w19 * w20
    mov w1, #4                                  // w1 <- 4
    mul w0, w0, w1                              // w0 *= 4
    bl malloc                                   // call malloc
    mov x21, x0                                 // x21 <- x0

    mov x0, x21                                 // x0 <- x21 
    mov w1, w19                                 // w1 <- w19 
    mov w2, w20                                 // w2 <- w20 
    bl ReadMatrix                               // call ReadMatrix
    
    adr x0, NewLine1                            // x0 <- &NewLine1
    bl printf                                   // call printf 

    mov x0, x21                                 // x0 <- x21 
    mov w1, w19                                 // w1 <- w19 
    mov w2, w20                                 // w2 <- w20 
    bl WriteMatrix                              // call WriteMatrix

    mov x0, x21                                 // x0 <- x21 
    mov w1, w19                                 // w1 <- w19 
    mov w2, w20                                 // w2 <- w20 
    bl CountDifferentLines                      // call CountDifferentLines
    mov w1, w0                                  // w1 <- w0 
    adr x0, MessageCountLinesFormat1            // x0 <- &MessageCountLinesFormat1
    bl printf                                   // call printf

    mov x0, x21                                 // x0 <- x21
    mov w1, w19                                 // w1 <- w19
    mov w2, w20                                 // w2 <- w20
    bl CountDifferentRows                       // call CountDifferentRows
    mov w1, w0                                  // w1 <- w0
    adr x0, MessageCountRowsFormat1             // x0 <- &MessageCountRowsFormat1
    bl printf                                   // call printf

    mov x0, x21                                 // x0 <- x21
    bl free                                     // call free 

    ldp x21, x20, [sp], #16
    ldp x19, x30, [sp], #16

    mov x0, #0                                  // return 0

    ret

MessageCountLinesFormat1:
    .asciz "Кол-во строк, все элементы которых различны: %d\n"

MessageCountRowsFormat1:
    .asciz "Кол-во столбцов, все элементы которых различны: %d\n"

NewLine1:
    .asciz "\n"
