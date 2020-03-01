//For lab 3
//COSC 130
//Shravan Pinni
//Did not work with anyone but took some advice from Professor Marz's lecture

#include <cstdio>
#include <string>

int add (int num1, int num2);
int main (int argc, char *argv[]){
	int numA;
	int numB;
	int result;
	printf("%s\n", "Enter two numbers to add: ");
	scanf("%d", &numA);
	scanf("%d", &numB);
	result  = add(numA, numB);
	printf("Result = %d\n",result); 
}

int add(int num1, int num2){
	while (num2 !=0){
		int carry  = num1 & num2;
		num1 = num1  ^ num2;
		num2 = carry << 1;
	}
	return num1;
}
