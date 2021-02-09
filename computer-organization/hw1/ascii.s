.section .text
.globl _start
li a0, 0x21         
li t3, 0x7F
loop:
# copy from util.s
WRITE_SERIAL:                       
    li t0, 0x10000000
.TESTW:
    lb t1, %lo(5)(t0)  
    andi t1, t1, 0x20      
    bne t1, zero, .WSERIAL          
    j .TESTW                        
.WSERIAL:
    sb a0, %lo(0)(t0)  
add a0, a0, 1
bne a0, t3, loop
ret
