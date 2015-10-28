	.data
	nom: .asciiz "Ingrese numero: "
	res: .asciiz "Resultado: "
		finStr: .asciiz "\n" #Cambio de linea
	.text
comienzo:
	li $s5, 30
	li $v0, 4
	la $a0, nom
	syscall	
	li $v0, 5	
	syscall
	add $s1, $v0, $zero
	add $s2, $s5, $zero
	bgez $s1,menor		#Evalua que el número sea positivo
	j comienzo


menor:
	sub $s3,$s2,$s1		#Evalua que el número sea menor a 30
	bgtz $s3,fibonacci
	j comienzo     

fibonacci:
	add $s3, $s1, $zero
	add $s1, $zero, $zero 		#Establece valores iniciales para iniciar el proceso
	li $s2, 1
	beqz, $s3,fin
	j ciclo

ciclo:
	li $v0, 1	
	add $a0, $s1, $zero	
	syscall 
	sub $s3, $s3, 1
	add $s4, $s1, $s2
	add $s1, $s2, $zero		#Realiza la suma de los números en un ciclo
	add $s2, $s4, $zero
	li $v0, 4
	la $a0, finStr
	syscall	
	bgtz $s3,ciclo
	beqz $s3,fin



fin:

	li $v0, 4
	la $a0, res
	syscall	
	li $v0, 1	
	add $a0, $s1, $zero	
	syscall 
	li $v0, 10	#Fin del programa
	syscall
