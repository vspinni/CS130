//program that generates a random number and forces the user to input it

.section .rodata

format:  .asciz "%d"
leftcarrot: .asciz "<< "
rightcarrot: .asciz ">> "

.section .text

.global main
main:
	
	bne		a0, 3, 2f
	
	addi	sp, -64(sp)
	sd		ra, 0(sp)
	sd		s0, 8(sp)
	sd		s1, 16(sp)
	sd		s2, 24(sp)
	sd		s3, 32(sp)
	sd		s4, 40(sp)

	mv		s0, 8(a1)
	mv		s1, 16(a1)

	mv		a0, s0
	la		a1, format
	addi	a2, sp, 48
	sscanf
	mv		

	mv		a0, s1
	la		a1, format
	addi	a2, sp, 56
	sscanf
		
	rand 
	sub		s2, s1, s0
	addi	s2, s2, 1
	rem		s2, a0, s2
	
	la		a1, 
	printf	
	


	
1:
	

2:
	ld		
	ret
