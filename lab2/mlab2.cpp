//Mini Lab 2
//COSC 130
//Shravan Pinni
//1/11/19
//Did not work with anyone individually but took some advice from Professor Marz during lecture

#include <cstdio>
#include <string>

//function prototypes
int Set (int original_number, int bit_index);
int Clear (int original_number, int bit_index);
int Test (int number, int bit_index);

int main (int argc, char *argv[]){

int i = 0;
i = Set (i,0);
printf ("%d\n", i);
i = Set (i,3);
printf ("%d\n", i);
i = Clear (i,0);
printf ("%d\n", i);
printf ("%d\n", Test(i, 0));
printf ("%d\n", Test(i, 3));
}
//Sets a bit's value at a certain index to 1
int Set (int original_number, int bit_index){

	return original_number | (1 << bit_index);
}

//Sets a bit's value at a certain index to 0
int Clear (int original_number, int bit_index){

	return original_number & ~(1 << bit_index);
}
//Returns a bit's value at a certain index
int Test (int number, int bit_index){

	return (number >> bit_index) & 1;
}
