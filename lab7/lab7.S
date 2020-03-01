//Lab 7
//Shravan Pinni
//COSC 130
//2/23/19
//Got help from Dr. Marz's mini lab solution and Aaron Vicke

.section .rodata

integer_scan: .asciz "%d"
char_scan: .asciz "%c"
not_enough: .asciz "Not enough arguments.\n"
too_many: .asciz "Too many arguments.\n"
result: .asciz "Result: %d %c %d = %d\n"
unknown: .asciz "Unknown Operator '%c'\n"

.section .text
//Function that adds the left and right operands
Addition:
	la		a0, result
	ld		a1, 32(sp)
	ld		a2, 40(sp)
	ld		a3, 48(sp)
	add		a4, a1, a3
	ret
//function that subtracts the right operand from left operand
Subtraction:
	la		a0, result
	ld		a1, 32(sp)
	ld		a2, 40(sp)
	ld		a3, 48(sp)
	sub		a4, a1, a3
	ret
//function that multiplies the right and left operands
Multiplication:
	la		a0, result
	ld		a1, 32(sp)
	ld		a2, 40(sp)
	ld		a3, 48(sp)
	mul		a4, a1, a3
	ret
//function that divides left operand by right operand
Division:
	la		a0, result
	ld		a1, 32(sp)
	ld		a2, 40(sp)
	ld		a3, 48(sp)
	div		a4, a1, a3
	ret
//function that divides left operand by right operand and returns the remainder
Modulus:
	la		a0, result
	ld		a1, 32(sp)
	ld		a2, 40(sp)
	ld		a3, 48(sp)
	rem		a4, a1, a3
	ret	

	

.global main
main:

//allocates space to stack pointer
	addi	sp, sp, -48
	sd		ra,	0(sp)

//checks command line arguments
	li		t0, 4
	blt		a0, t0, 1f
	bgt		a0, t0, 2f

//saves the save registers
	sd		s0, 8(sp)
	sd		s1, 16(sp)
	sd		s2, 24(sp)

//loads the argv values into the saved registers
	ld		s0, 8(a1)
	ld		s1, 16(a1)
	ld		s2, 24(a1)

//converts the first argument using sscanf
	mv		a0, s0
	la		a1, integer_scan
	addi	a2, sp, 32
	call	sscanf
//converts the second argument using sscanf
	mv		a0, s1
	la		a1, char_scan
	addi	a2, sp, 40
	call	sscanf
//conerts the third argument using sscanf
	mv		a0, s2
	la		a1, integer_scan
	addi	a2, sp, 48
	call	sscanf

//checks which operation to use and jumps to the proper label
	lb		a1, 40(sp)
	li		t1, '+'
	beq		a1, t1, 3f
	li		t1, '-'
	beq		a1, t1, 4f
	li		t1, '/'
	beq		a1, t1, 5f
	li		t1, 'x'
	beq		a1, t1, 6f
	li		t1, '%'
	beq		a1, t1, 7f

	j		8f


//label for not enough arguments
1:
	la		a0, not_enough
	call	printf
	j		exit
//label for too many arguments
2:
	la		a0, too_many
	call	printf
	j		exit

//label for the addition function call
3:
	call	Addition
	call	printf
	j		exit

//label for subtraction function call
4:
	call	Subtraction
	call	printf
	j		exit

//label for division function call
5:
	call	Division
	call	printf
	j		exit

//label for multiplication function call
6:
	call	Multiplication
	call	printf
	j		exit

//label for modulus function call
7:
	call	Modulus
	call	printf
	j		exit

8:
	la		a0, unknown
	call	printf
	j		exit

//label for an exit protocol that gives stack memory back
exit: 
	ld		ra, 0(sp)
	ld		s0, 8(sp)
	ld		s1, 16(sp)
	ld		s2, 24(sp)
	addi	sp, sp, 48 
	ret












