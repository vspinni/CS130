//lab 3 - Bit by bit calculator for ints
//COSC 130
//Shravan Pinni
//1/25/19
//Worked with Refati, used Dr. Marz's mini lab solution for the add function

#include <cstdio>
#include <string>


int sign(int value);
int twos(int value);
int add(int left, int right);
int sub(int left, int right);
int mul(int left, int right);

int main(int argc, char *argv[])
{
	if (argc < 4) {
		printf("Usage: %s <num> <op> <num>\n", argv[0]);
			return -1;
	}
	int left;
	int right;
	char op;
	int result;
	sscanf(argv[1], "%d", &left);
	sscanf(argv[2], "%c", &op);
	sscanf(argv[3], "%d", &right);
	switch (op)
	{
		case '+':
			result = add(left, right);
			break;
		case '-':
			result = sub(left, right);
			break;
		case 'x':
			result = mul(left, right);
			break;
		default:
			printf("Unknown operation '%c'\n", op);
			return -2;
	}
	printf("%d %c %d = %d\n", left, op, right, result);

			return 0;
}

//Returns the sign of a value by taking the leftmost bit and bitwise  & it with 1
int sign (int value){
	
	return ((value>>31) & 1);
}

//Inverts the given value using bitwise NOT and then uses the created add function to add 1
int twos (int value){

return add (~value, 1);	
}

//Dr. Marz's mini lab solution
int add (int left, int right){
	int carry = 0;
	int sum = 0;
	
	for (int i = 0;i<32;i++){
		int l = (left >> i) & 1;
		int r = (right >> i) & 1;
		int s = l ^ r ^ carry;
		carry  = (l & r) | (r & carry) | (l & carry);
		sum = sum | (s << i);
	}
	return sum;
}

// uses the add function with the twos complement of the right value because subtracting is the same as adding a negative
int sub(int left, int right){

	return (add(left, twos(right)));
}

//multiplies the left bit with the right bit
int mul(int left, int right){

	// takes the signs of the left and rigt values and stores them
	int signl = sign(left);
	int signr = sign(right);

	//creates variables for the product, the place, and a temporary left to be added to the product
	int product = 0;
	int place = 0;
	int leftT;
	//determines the sign of the product by using XOR
	int sign = signl ^ signr;

//performs the twos complement on negative inputs
	if(signl)
		left = twos(left);

	if(signr)
		right = twos(right);
	
	while (right != 0){
//sets the rightmost bit of the right value as the multiplier bit
		int multiplier = right & 1 ;
//if the multiplier bit is one, the temporary left value is shifted left by the current place and then added to the product
		if(multiplier)
		{
			leftT = left<<place;
			product	 = add (product,leftT);
		}
		//the place is incremented and the right is shifted right once so the multiplier bit is the next one along the line
		place  = add (place, 1);
		right = right >> 1;

	}
	//takes the twos complement of the product if its determined sign is negative
	 if(sign){
		product = twos(product);
	 }

	return product;
}
