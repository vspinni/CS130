//Mini lab8
//COSC 130
//Shravan Pinni
//2/28/19
//Worked with no one
.section .text

.section .rodata

.global main
main:

	li		t0,0
	li		t1, 7
	li		t2, 0

1: 
	bge		t0, t1, 1f
	ld		t3, 0(a0)
	add		t2, t2, t3
	addi	t0, t0, 1
	addi	a0, a0, 4
	j		1b

1:	
	ret
