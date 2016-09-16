.text
.global main
main:
addiu $sp, $sp, -20
addi $t2, $t2, 4
end:
add $t0, $t4, $t5
addu $t7, $t6, $t4
and $t1, $t7, $t0
beq	 $t1, $zero, end
sll $t0, $t1, -2
slt $12, $10, $13
lw $t3, 8($sp)
j main
