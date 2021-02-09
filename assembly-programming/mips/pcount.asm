.rdata
    newline:
    .asciiz "\n"   

.text
.globl main
main:
    subu        $sp, $sp, 32    # stack frame is 32 bytes long
    sw          $ra, 20($sp)    # save return address
    sw          $fp, 16($sp)    # save old frame pointer 

    li          $a0, -1        # input 
    move	    $v1, $a0		# save input to $v1
    li          $v0, 1          # print input
    syscall
    li          $v0, 4
    la          $a0, newline    # print newline
    syscall

    move	    $a0, $v1		# restore input
    jal         pcount_r        # call pcount_r

    move 	    $a0, $v0		# ret as print argument
    li          $v0, 1          # print
    syscall
    li          $v0, 4
    la          $a0, newline    # print newline
    syscall

    lw          $ra, 20($sp)    # restore ret addr
    lw          $fp, 16($sp)    # restore frame pointer
    addiu       $sp, $sp, 32    # pop stack fram

    li          $v0, 10       
    syscall                     # terminate

pcount_r:
    subu        $sp, $sp, 32    # stack frame is 32 bytes long
    sw          $ra, 20($sp)    # save return address
    sw          $fp, 16($sp)    # save old frame pointer
    addiu       $fp, $sp, 28    # set up frame pointer (4 bytes reserved)
    sw          $a0, 0($fp)     # save argumnet x

    lw          $v0, 0($fp)     # load x
    beq         $v0, $zero, $L2    #branch if n == 0
    srl         $a0, $a0, 1
    jal         pcount_r        # call pcount_r
    lw          $v1, 0($fp)     # load x
    andi        $v1, $v1, 1     # v1 = x & 1
    addu        $v0, $v0, $v1   # compute ret = x & 1 + pcount_r(x >> 1)
    jr          $L1             # jump code to return  

$L2:    # if n == 0 then
    li          $v0, 0          # return 0

$L1:
    lw          $ra, 20($sp)    # restore $ra
    lw          $fp, 16($sp)    # restore $fp
    addiu       $sp, $sp, 32    # pop stack
    jr          $ra             # return to calller
    