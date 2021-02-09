.section .text
.globl _start
_start:
    li      a0, 1       # fib1 low
    li      a1, 0       # fib1 high
    li      a2, 1       # fib2 low
    li      a3, 0       # fib2 high
    li      t4, 0       # counter
    li      t5, 58
fib:
    # high
    mv      t0, a3
    add     a3, a3, a1
    mv      a1, t0
    # low
    mv      t0, a2
    add     a2, a2, a0
    bgeu    a2, t0, no_carry    # new a2 >= old a2 (unsigned), no overflow
    add     a3, a3, 1   # carry
no_carry:
    mv      a0, t0
    addi    t4, t4, 1
    bne     t4, t5, fib
    la      t0, 0x80400000
    sw      a2, 0(t0)
    sw      a3, 4(t0)
    ret
    