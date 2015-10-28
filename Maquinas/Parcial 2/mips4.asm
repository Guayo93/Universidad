.data
	paal: .asciiz "asdfasdf"
.text
	li $t0, 0 #contador letras
	la $s0, paal #palabra
	li $t1, 0 #contador loop
	
	contarLetras:
	  lb $t2, 0($s0) #char actual
	  beqz $t2, preloop
	  add $s0, $s0, 1
	  add $t0, $t0, 1
	  j contarLetras
	
	preloop:
	  sub $s0, $s0, $t0
	loop:
	  add $t3, $t1, $zero #temporal loop
	  li $t4, 2 #divisor
	  div $t3, $t4
	  mfhi $t5 #residuo
	  beq $t5, 0, aMayus
	  add $t1, $t1, 1
	  bne $t1, $t0, loop
	  j fin
	  
	aMayus:
	  add $s0, $s0, $t1
	  lb $t2, 0($s0)
	  subi $t2, $t2, 32
	  sb $t2, ($s0)
	  sub $s0, $s0, $t1
	  add $t1, $t1, 1
	  j loop
	  
	fin:
	  li $v0, 4
	  la $a0, paal
	  syscall
	  li $v0, 10
	  syscall
