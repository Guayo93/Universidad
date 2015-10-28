.data
	pal1: .asciiz "asdf"
	pal2: .asciiz "qwer"
.text
	la $s0, pal1
	la $s1, pal2
	
	lb $t0, 0($s0)
	lb $t1, 0($s1)
	
	xor $t2, $t0, $t1
	li $v0, 1
	la $a0, ($t2)
	syscall
	li $v0, 10
	syscall