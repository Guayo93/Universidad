.data
	buffer: .space 15
	nom: .asciiz "Ingrese nombre: "
	ape: .asciiz "Ingrese apellido: "
	str: .ascii "  "
	nombre: .space 15
	apellido: .space 15
	fraFin: .ascii "El resultado es: "
	todoFin: .space 45
	xorFin: .ascii "El XOR entra la primera letra del Nombre y el Apellido es: "
	
.text
	#-----------------------NOMBRE-------------------------
	
	li $v0, 4
	la $a0, nom
	syscall
	
	li $v0, 8
	la $a0, buffer
	la $a1, 15
	move $s0, $a0
	syscall	
	
	#Copiado a .data
	la $t0, nombre
	miniloop:
	lb $t2, ($s0)
	beqz $t2, finLoop
	sb $t2, ($t0)
	add $s0, $s0, 1
	add $t0, $t0, 1
	j miniloop
	finLoop:
	
	#------------TODO A MINUS-----------
	
	  la $t0, nombre
	aMinus:
	  lb $t2, ($t0)
	  beqz $t2, fin1
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
	fin1:
	
	#------------------CAMBIO DE LETRAS--------------------
	
	la $s0, nombre #palabra
	li $t0, 0 #contador letras
	li $t1, 0 #contador loop

	contarLetras:
	  lb $t2, 0($s0) #char actual
	  beqz $t2, preloop
	  add $s0, $s0, 1
	  add $t0, $t0, 1
	  j contarLetras
	
	preloop:
	  sub $s0, $s0, $t0
	  sub $s0, $s0, 1
	  
	loop:
	  add $t3, $t1, $zero
	  li $t4, 2 #divisor
	  div $t3, $t4
	  mfhi $t5 #residuo
	  beq $t5, 0, aMayus
	  add $t1, $t1, 1
	  blt $t1, $t0, loop
	  j fin2
  
	aMayus:
	  add $s0, $s0, $t1
	  lb $t2, 0($s0)
	  subi $t2, $t2, 32
	  sb $t2, ($s0)
	  sub $s0, $s0, $t1
	  add $t1, $t1, 1
	  j loop
  
	fin2:
	
	#----------------------APELLIDO--------------------------------
	
	li $v0, 4
	la $a0, ape
	syscall	
	
	li $v0, 8
	la $a0, buffer
	la $a1, 15
	move $s0, $a0
	syscall	
	
	#Copiado a .data
	la $t0, apellido
	miniloop2:
	lb $t2, ($s0)
	beqz $t2, finLoop2
	sb $t2, ($t0)
	add $s0, $s0, 1
	add $t0, $t0, 1
	j miniloop2
	finLoop2:
	
	#------------TODO A MINUS-----------
	
	  la $t0, apellido
	aMinus2:
	  lb $t2, ($t0)
	  beqz $t2, fin3
	  li $t1, 'A'
	  bge $t2, $t1, pruebaMayus2
	  j iter2
	pruebaMayus2:
	  li $t1, 'Z'
	  ble $t2, $t1, esMayus2
	iter2:
	  addi $t0, $t0, 1
	  j aMinus2
	esMayus2:
	  addi $t2, $t2, 32
	  sb $t2, ($t0)
	  j iter2
	fin3:
	
	#------------------CAMBIO DE LETRAS--------------------
	
	la $s0, apellido #palabra
	li $t0, 0 #contador letras
	li $t1, 0 #contador loop

	contarLetras2:
	  lb $t2, 0($s0) #char actual
	  beqz $t2, preloop2
	  add $s0, $s0, 1
	  add $t0, $t0, 1
	  j contarLetras2
	
	preloop2:
	  sub $s0, $s0, $t0
  	  sub $s0, $s0, 1
	  
	loop2:
	  add $t3, $t1, $zero
	  li $t4, 2 #divisor
	  div $t3, $t4
	  mfhi $t5 #residuo
	  beq $t5, 0, aMayus2
	  add $t1, $t1, 1
	  blt $t1, $t0, loop2
	  j fin4
  
	aMayus2:
	  add $s0, $s0, $t1
	  lb $t2, 0($s0)
	  subi $t2, $t2, 32
	  sb $t2, ($s0)
	  sub $s0, $s0, $t1
	  add $t1, $t1, 1
	  j loop2
  
	fin4:
	
	#--------------------IMPRESION FINAL--------------------------
	
	li $v0, 4
	la $a0, fraFin
	syscall
	
	la $s0, todoFin
	la $s1, nombre
	la $s2, str
	la $s3, apellido
	
	copiaNombre:
	  lb $t0, ($s1)
	  beqz $t0, precopia
	  sb $t0, ($s0)
	  addi $s0, $s0, 1
	  addi $s1, $s1, 1
	  j copiaNombre
	  
	precopia:
	  sub $s0, $s0, 1
	  
	copiaStr:
	  lb $t0, ($s2)
	  beqz $t0, copiaApellido
	  sb $t0, ($s0)
	  addi $s0, $s0, 1
	  addi $s2, $s2, 1
	  j copiaStr
	  
	copiaApellido:
	  lb $t0, ($s3)
	  beqz $t0, fin5
	  sb $t0, ($s0)
	  addi $s0, $s0, 1
	  addi $s3, $s3, 1
	  j copiaApellido
	  
	fin5:
	  li $v0, 4
	  la $a0, todoFin
	  syscall
	
	#-------------------------XOR------------------------------
	
	la $s0, nombre
	la $s1, apellido
	
	lb $t0, 0($s0)
	lb $t1, 0($s1)
	
	xor $t2, $t0, $t1
	
	li $v0, 4
	la $a0, xorFin
	syscall
	
	li $v0, 1
	la $a0, ($t2)
	syscall
	
	#----------------------------FIN------------------------------
	
	li $v0, 10
	syscall