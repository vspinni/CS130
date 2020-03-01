//Lab 9
//Shravan Pinni
//COSC 130
//3/28/19

.section .rodata

	invalid: .asciz "Usage: ./lab 0x<address>\n"
	columns: .asciz "  Level   Index  Btye Offset\n"
	printVPN: .asciz "VPN[%03d] = %-4d (%4d)\n"
	po: .asciz "PO       = %lx\n"

	hex_scan: .asciz "%lx"

.section .text

.global main 
main:

//moving stack pointer and allocates space to the saved registers
	addi	sp, sp, -64
	sd		ra, 0(sp)
	sd		s0, 8(sp)  //stores virtual address
	sd		s1, 16(sp) //iterator, starts at 2
	sd		s2, 24(sp) //holds the comparison to the iterator, 0
	sd		s3, 32(sp) //index
	sd		s4, 40(sp) //right shift
	sd		s5, 48(sp) //offset

//Checks command line arguments
	li		t0, 2
	bne		a0, t0, 4f
	
//takes the hex number from command line and puts it in s0
	ld	s0, 8(a1)

//sscanf to convert the char* hexnumber into an integer
	mv		a0, s0
	la		a1, hex_scan
	addi	a2, sp, 56
	call	sscanf

//moves the result from sscanf and stores it in s0
	ld		s0, 56(sp)	

//initializes the saved registers
	li		s1, 2  //initializes the iterator to 2
	li		s2, -1  //comparison to the for loop iterator, -1
	mv		s3, s0 //copies the virtual address in another variable to be used in the for loop
	li		s4, 30 //puts the amoount to right shift by into s4
	li		s5, 0  //initializes the offset as 0
	
1: //for loop
//compares the iterator = -1 as the jump condition
	beq		s1, s2, 2f 		

//shifts the hex value by the right shift value and storing it in the hex value copy
	sra		s3, s0, s4

//ands it with 1ff to extract the VPN parts
	li		t1, 511
	and		s3, s3, t1

//calculates the offset by taking the result of the and command and multiplying it with 8
	li		t4, 8
	mul		s5, s3, t4

//prints the VPN piece
	la		a0, printVPN
	mv		a1, s1
	mv		a2, s3
	mv		a3, s5
	call	printf

//decrements the right shift and the iterator
	addi	s4, s4, -9
	addi	s1, s1, -1
	j		1b

2://after for loop
//ands the original vpn address with fff to get the PO and prints it
	li		t2, 4095
	and		t3, s0, t2
	la		a0, po
	mv		a1, t3
	call	printf

//returns the saved registers and stack pointer to original conditions
3:
	ld		ra, 0(sp)
	ld		s0, 8(sp)
	ld		s1, 16(sp)
	ld		s2, 24(sp)
	ld		s3, 32(sp)
	ld		s4, 40(sp)
	ld		s5, 48(sp)
	addi	sp, sp, 64 
	ret

//branch for an invalid address that prints usage and returns the saved registers and stack pointer to original conditions
4:
	la		a0, invalid
	call	printf 
	ld		ra, 0(sp)
	ld		s0, 8(sp)
	ld		s1, 16(sp)
	ld		s2, 24(sp)
	ld		s3, 32(sp)
	ld		s4, 40(sp)
	ld		s5, 48(sp)
	addi	sp, sp, 64 
	ret
	
