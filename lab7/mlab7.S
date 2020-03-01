//For Lab 7
//Shravan Pinni
//COSC 130
//2/22/19
//Got help from Refati Rusitanmu

.section .rodata

LA: .asciz "Not enough arguments."
GG: .asciz " "

.section .text
.global main

main: 

	addi	sp, sp, -32 //allocates 32 bytes of space from stack
	sd		ra, 0(sp) //save return address
	sd		s0, 8(sp) //allocating space for 3 registers
	sd		s1, 16(sp)
	sd		s2, 24(sp)
	mv		s0, a0  //putting a0 into s0 and a1 into s1
	mv		s1, a1
	li		s2, 4
	blt		s0, s2, 1f	//compares 4 to the number of arguments and switches labels based off the response
	j		2f

1: mv		a0, s1	
   ld		a0, 24(a0)
   call		printf
   j		3f


2: mv		a0, s1		//
   ld		a0, 24(a0)
   call		printf
   la		a0, GG
   call		printf
   mv		a0, s1
   ld		a0, 16(a0)
   call		printf
   la		a0,GG
   call		printf
   mv		a0, s1
   ld		a0, 8(a0)
   call		printf
   j		3f

3: ld		ra, 0(sp)
   ld		s0, 8(sp)
   ld		s1, 16(sp)
   ld		s2, 24(sp)
   addi		sp, sp, 32
   ret
