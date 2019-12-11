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
    str x26, [sp, #-8]!

    mov x23, x0                                 // x23 <- x0
    mov w24, w1                                 // w24 <- w1
    sxtw x25, w2                                // x25 <- w2

    mov x26, #0									// x26 <- 0

    mov w19, #0                                 // x19 <- 0

    // for (w20 = 0, w20 < w24, w20++)
    Loop3_Start:
        mov w20, #0                             // w20 <- 0
        b Loop3_Check                           // goto Loop3_Check
        Loop3_Body:
			mov x0, #4							// x0 <- 4
            madd x0, x26, x0, x23				// x0 <- x26 * 4 + x23 
            mov w1, #1                          // w1 <- 1
            mov x2, x25                         // x2 <- x25

            bl CheckAllDifferent                // call CheckAllDifferent
            cmp w0, #0                          //  if x0 == false
            b.eq Loop3_Continue                 //  goto Loop3_Continue
            add w19, w19, #1                    // w19++
            Loop3_Continue:
                add x26, x26, x25				// x26 += x25
                add w20, w20, #1                // x20++
        Loop3_Check:
            cmp w20, w24                        //  if x20 < x24
            b.lt Loop3_Body                     //  goto Loop3_Body

    mov w0, w19									// w0 <- w19

    ldr x26, [sp], #8
    ldr x25, [sp], #8
    ldr x24, [sp], #8
    ldr x23, [sp], #8
    ldr x20, [sp], #8
    ldr x19, [sp], #8
    ldr x30, [sp], #8

    ret											// return w0 = w19

    .global	CountDifferentRows
CountDifferentRows:
    str x30, [sp, #-8]!
    str x19, [sp, #-8]!
    str x20, [sp, #-8]!
    str x23, [sp, #-8]!
    str x24, [sp, #-8]!
    str x25, [sp, #-8]!

    mov x23, x0                                 // x23 <- x0
    mov w24, w1                                 // w24 <- w1
    mov w25, w2                                 // w25 <- w2


    mov w19, #0                                 // w19 <- 0

    // for (w20 = 0, w20 < w25, w20++)
    Loop4_Start:
        mov w20, #0                             // w20 <- 0
        b Loop4_Check                           // goto Loop4_Check
        Loop4_Body:
			mov x0, #4							// x0 <- 4
            madd x0, x20, x0, x23				// x0 <- x20 * 4 + x23
            mov w1, w25                         // w1 <- w25
            mov w2, w24                         // w2 <- w24
            bl CheckAllDifferent                // call CheckAllDifferent
            cmp w0, #0                          //  if x0 == false
            b.eq Loop4_Continue                 //  goto Loop4_Continue
            add w19, w19, #1                    // w19++
            Loop4_Continue:
                add w20, w20, #1                // w20++
        Loop4_Check:
            cmp w20, w25                        //  if w20 < w25
            b.lt Loop4_Body                     //  goto Loop4_Body

    mov w0, w19									// w0 <- w19

    ldr x25, [sp], #8
    ldr x24, [sp], #8
    ldr x23, [sp], #8
    ldr x20, [sp], #8
    ldr x19, [sp], #8
    ldr x30, [sp], #8

    ret											// return w0 = w19

DecimalIntDebugFormat:
    .asciz "|l-%d--"


DecimalIntDebugFormat1:
    .asciz "|r--%d-"

DecimalIntDebugFormat2:
    .asciz "|a--%d--"
