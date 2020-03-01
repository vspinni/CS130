//Lab 8
//Shravan Pinni
//COSC 130
//3/7/19
//Got some help from Aaron Vick

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
	addi  a2, a2, 1      //incrementor for character in search
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
	ret                  //returns a0

7: //End
	ret                  //returns a0

