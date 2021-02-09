.section .text
.globl _start
_start:
    la      t3, 0x80400000  # mem start address
    addi    t4, t3, 36      # mem end address
    li      a0, 1
    li      a1, 1
    sw      a0, 0(t3)
    addi    t3, t3, 4
    sw      a1, 0(t3)  
fib:
    addi    t3, t3, 4
    add     t0, a0, a1
    mv      a0, a1
    mv      a1, t0
    sw      a1, 0(t3)
    bne     t3, t4, fib     # end loop if t3 == t4
    ret