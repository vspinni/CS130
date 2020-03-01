//Lab 8
//Shravan Pinni
//COSC 130
//3/7/19
//Got assistance from Aaron Vick, Chase Hunter, Refati Rusitanmu

.section .text

.global Search
Search:
  
  
//NOS Table  
//                 Name         Offset        Size
// name            char[51]		0             51
// age			   int          52            4
//gender           char         56            1
//padding = 3, total size of person 60

//loading temporary registers
  li	t0,  0    //Byte Counter
  li	t1,  0    //Gender
  li	t3,  0	  //Person Counter
  li    t4,  0    //Search Char
  li    t5,  0    //Array Char
  li	t6,  0    //Age

//moves from person to person
1: //Person
	beq		a1, t3, 6f     //checks if the array is done or not and directs to null ptr
	addi	t3, t3, 1      //increments person counter

//For loop for each character in loop
2: //Chars in name
	beq		t5, zero, 3f   //for loop condition to check if the name is done
	lb		t4, 0(a2)      //loads a char from the person being looked for
	lb		t5, 0(a0)      //loads a char from the person in the array
	addi	a0, a0, 1      //incrementor for the character in array
	addi    a2, a2, 1      //incrementor for character in search
	addi	t0, t0, 1      //increments byte counter
	beq		t4, t5, 2b     //checks if the characters are equal
	bne		t4, t5, 5f     //checks if the characters are not equal

3: //Age
	sub		a0, a0, t0     //resets the pointer position
	addi	a0, a0, 52     //puts the pointer position at 52
	lw		t6, 0(a0)      //loads the age into a temporary register so it can be compared
	beq		t6, a3, 4f     //checks if the ages are equal
	bne		t6, a3, 5f     //checks if the ages are not equal

	
4: //Gender
	addi	a0, a0, 4      //moves the pointer up by 4
	lb		t1, 0(a0)      //loads the gender into a temporary register
	bne		t1, a4, 5f     //checks to see if the genders are not equal
	beq		t1, a4, 7f     //checks to see if the genders are equal


5: //Not equal
	sub		a0, a0, t0     //resets the pointer of a0 from wherever it stopped
	sub		a2, a2, t0     //resets the pointer on name from where it was
	sub		t0, t0, t0     //resets the byte counter
	addi	a0, a0, 60     //moves to the next person

6: //Null ptr
	li		a0, 0          //returns 0 of the person is not found
	ret                    //returns a0

7: //End
	ret                    //returns a0


	
   
  

.global Median
Median:
	addi	sp, sp, -32		//allocates 32 bytes from stack
	sd		ra, 0(sp)		//saves the first 8 bytes allocated for the return address
	sd		s0, 8(sp)		//saves the next 8 bytes for s0
	sd		s1, 16(sp)		//saves the next 8 bytes for s1
	sd		s2, 24(sp)		//saves the last 8 bytes for s2


	li		t0, 0			//iterator for the copying loop
	li		t1, 0			//intermediate location from first array and buffer array

1: //Copies initial array into the buffer array
	bge		t0, a1, 2f      //t0 >= array.length jump to 2
	lw		t1, 0(a0)       //loads the number from a0 into t1
	sw		t1, 0(a2)       //saves the t1 into the buffer
	addi	a0, a0, 4       //increments the pointer for the initial array
	addi	a2, a2, 4		//increments the pointer for the buffer
	addi	t0, t0, 1       //increments the iterator
	j		1b              //jumps back for the loop

2: //Setting up registers for the bubble sort algorithm
	li		t0, 0			//int i, iterator for outer loop
	li		t1, 0			//int j, iterator for inner loop

	mv		t2, a1			//comparison for i, array size
	addi	t2, t2, -1		//array.size -1

	mv		t3, t2			//comparison for j, array.size -1- i 

	//loaded 0 into the registers I havent used yet as a reminder
	li		t4, 0
	li		t5, 0			
	li		t6, 0			
	li		s0, 0			
	li		s1, 0			
	li		s2, 0			



3: //for loop 1
	bge		t0, t2, 7f		//condition to end the outer loop, i <=array.size -1
	li		t1, 0			//resetting j at the start of every inner loop

4: //for loop 2
	sub		t3, t2, t0		//t3 = array.size - 1 - i 
	bge		t1, t3, 6f		//if j >= t3, jump to 6
	lw		s0, 0(a2)		//saves the value at array[j] in s0
	lw		s1, 4(a2)		//saves the value at array[j+1] in s1
	bgt		s0, s1, 5f		//if array[j] > array[j+1] jump to the if statement
	addi	a2, a2, 4		//move the a2 pointer forward by 4
	addi	t1, t1, 1		//j++
	j		4b				//going back up to the nested loop

5: //if statement for swapping
	sw		s0, 4(a2)		//array[j+1] = s1(array[j])
	sw		s1, 0(a2)		//array[j] = s0(array[j+1])
	addi	t1, t1, 1		//j++
	addi	a2, a2, 4		//moving the a2 pointer by 2
	j		4b				//moving back into the nested for loop

6://part 2 of for loop 1
	li		t4, 4			//sets t4 = 4
	mul		t4, t1, t4		//t4 = i * 4
	sub		a2, a2, t4		//moves the a2 pointer back by the amount that it was moved forward in the nested loop
	addi	t0, t0, 1		//increments i
	j		3b				//goes back to the start of the first loop
	
	
7: //Checking is the array size is even or odd
	li		t0, 0			//Loading 0 into t0 to use with mod
	li		t1, 2			//Loading 2 into t1 to use with beq and labels 8 and 9
	li		t2, 4			//Loading 4 into t3 to use with the labels 8 and 9
	rem		t3, a1, t1		//t3 = array.size % 2
	beq		t3, t0, 9f		//Ef t2 == 0, jump to 9 for even median
	j		8f				//Else jump to 8 for odd median

8: //Odd Median
	li		t3, 0			//resetting t3
	div		t3, a1, t1		//t3 = array.size / 2
	mul		t3, t3, t2		//t3 = array.size / 2 * int size (4)
	add		a2, a2, t3		//move the a2 pointer to position t3
	lw		t4, 0(a2)		//load the value at a2 pointer into t4
	mv		a0, t4			//move t4 into a0
	j		10f				//jump to the exit label

9: //Even Median
	li		t3, 0			//resets t3
	div		t3, a1, t1		//t3 = array.size / 2
	mul		t3, t3, t2		//t3 = array.size / 2 * int size (4)
	add		a2, a2, t3		//moves the a2 pointer to position t3
	lw		t4, 0(a2)		//loads the value at a2 pointer into t4
	lw		t5, 4(a2)		//loads the next value after the one at the position of a2 pointer into t5
	add		t4, t5, t4		//t4 = t4 + t5
	div		t4, t4, t1		//t4 = t4 / 2
	mv		a0, t4			//moves t4 into a0
	j		10f				//jump to exit label

10: //Exit Label - gives all saved memory back to stack and returns a0
	ld		ra, 0(sp)	
	ld		s0, 8(sp)	
	ld		s1, 16(sp)	
	ld		s2, 24(sp)	
	addi	sp, sp, 32	
	ret						

	 



