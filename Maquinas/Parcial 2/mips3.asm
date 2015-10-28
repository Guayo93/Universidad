.data
		paal: .asciiz "HAsJDhASJ"
	.text 
		  la $t0, paal
		aMinus:
		  lb $t2, ($t0)
		  beqz $t2, fin
		  li $t1, 'A'
		  bge $t2, $t1, pruebaMayus
		  j iter
		pruebaMayus:
		  li $t1, 'Z'
		  ble $t2, $t1, esMayus
		iter:
		  addi $t0, $t0, 1
		  j aMinus
		esMayus:
		  addi $t2, $t2, 32
		  sb $t2, ($t0)
		  j iter
		fin:
		  li $v0, 4
		  la $a0, paal
		  syscall
		  li $v0, 10
		  syscall
