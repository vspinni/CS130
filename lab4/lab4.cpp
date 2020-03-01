//Lab 4
//COSC 130
//Shravan Pinni
//2/1/19
// Got help from John Sadik

#include <cstdio>

struct Real
{
     //sign bit
     int sign;
     //UNBIASED exponent
     long exponent;
     //Fraction including implied 1 at bit index 23
     unsigned long fraction;
};

//Prototypes for functions, some are from lab 3 as well
Real Decode(int float_value);
int Encode(Real real_value);
Real Normalize(Real value);
Real Multiply(Real left, Real right);
Real Add(Real left, Real right);
long AddInt (long left, long right);
long twos (long value);
long mul(long left, long right);

//int main
int main(int argc, char *argv[])
{
     int left, right;
     char op;
     int value;
     Real rLeft, rRight, result;
     if (argc < 4) {
          printf("Usage: %s <left> <op> <right>\n", argv[0]);
          return -1;
     }
     sscanf(argv[1], "%f", (float *)&left);
     sscanf(argv[2], "%c", &op);
     sscanf(argv[3], "%f", (float *)&right);
     rLeft = Decode(left);
     rRight = Decode(right);
     if (op == 'x') {
          result = Multiply(rLeft, rRight);
     }
     else if (op == '+') {
          result = Add(rLeft, rRight);
     }
     else {
          printf("Unknown operator '%c'\n", op);
          return -2;
     }
	 value = Encode(result);
     printf("%.3f %c %.3f = %.3f (0x%08x)\n",
            *((float*)&left),
            op,
            *((float*)&right),
            *((float*)&value),
            value
            );
     return 0;
}

//Decodes a float value and returns an int
Real Decode(int float_value)
{
	Real binNum;
	binNum.sign = (float_value >> 31) & 1;
	binNum.exponent = ((float_value >> 23) & 0xff) - 127;
	binNum.fraction = float_value & 0x7fffff;
	binNum.fraction = binNum.fraction | (1<<23);

	return binNum;
}


//Encodes a real value into a integer
int Encode(Real real_value)
{
	int num;

	num = real_value.sign << 31;
	num |= (((real_value.exponent + 127) & 0xff) << 23);
	num |= real_value.fraction & 0x7fffff;

	return num;
}
//Normalizes floating point result after a function
Real Normalize(Real value)
{
	Real copy = value;
	int i= 63;
//Searches for the first 1 in the fraction
	while(((copy.fraction >> i) & 1)==0)
		i--;
//If the position of the first 1 is greater than 23, the exponent is moved over 
	if( i > 23){
		copy.fraction >>= i-23;
		copy.exponent += i-23;
	}
//If the position of the first one is less than 23, it 23
	if ( i < 23){
		copy.fraction <<= 23-i;
		copy.exponent -= 23-i;
	}

	return copy;	
}

//Multiplies floating points
Real Multiply(Real left, Real right)
{
	
	Real product;
//XOR for the sign
	product.sign = left.sign ^ right.sign;
//Adds the exponents of the two inputs
	product.exponent = AddInt(left.exponent, right.exponent);
//binary multiplication of the input fractions
	product.fraction = mul(left.fraction, right.fraction);	
	product.fraction = product.fraction>>23;
//Normalizes the resulting fraction and exponent
	product = Normalize(product);
	return product;
}
//Adds floating points
Real Add(Real left, Real right)
{
//Declaring variables
	Real sum;
//Signs of the inputs
	int lsign = left.sign;
	int rsign = right.sign;
//fraction values of the inputs
	long leftFr = left.fraction;
	long rightFr = right.fraction;
//difference in the exponents, used to balance out the exponents
	long expDif = left.exponent-right.exponent;

//Accounts for inputs that either are or result in 0 since 0 is abnormal in IEEE-754
	if(left.fraction == 0x800000 && left.exponent ==-127)
		return right;
	if(right.fraction == 0x800000 && right.exponent ==-127)
		return left;
	if ((AddInt(right.fraction, twos(left.fraction)) ==0) || (AddInt(left.fraction,twos(right.fraction)) ==0)){
		sum.sign=0;
		sum.exponent = -127;
		sum.fraction = 0;
		return sum;
	}
			
//Shifts the exponents and fraction decimal based on the exponent difference and its direction
	if( expDif > 0 ){
		left.exponent = AddInt(left.exponent, twos(expDif));
		left.fraction <<=expDif;
	}
	else if(expDif < 0){
		right.exponent = AddInt(right.exponent, expDif);
		right.fraction <<=twos(expDif);
	}
	else{};
	sum.exponent = left.exponent;

//If statements for twos complement
	if(left.sign==1){
		left.fraction = twos(left.fraction);
	}
	if(right.sign==1){
		right.fraction = twos(right.fraction);
	}
	
//Adds the fractions after matching the exponents
	sum.fraction = AddInt(left.fraction, right.fraction);
	
//If else statements for the sign bit and whether a return twos complement is needed	
	if (rsign ==0 && lsign==0){
		sum.sign = 0;
	}
	else if(rightFr>leftFr && rsign==1 ){
		sum.sign = 1;
		sum.fraction = twos(sum.fraction);
	}
	else if (leftFr > rightFr && rsign ==1){
		sum.sign = 0;
	}
	else if(leftFr > rightFr && lsign ==1){
		sum.sign = 1;
		sum.fraction  = twos(sum.fraction);
	}
	else if(rightFr > leftFr && lsign ==1){
		sum.sign = 0;
	}
	else {
		sum.sign = 1;
		sum.fraction = twos(sum.fraction);
	}
	

	return Normalize(sum);
}


//Add function from my lab 3
long AddInt (long left, long right){
	long carry = 0;
	long sum = 0;
	
	for (long i = 0;i<64;i++){
		long l = (left >> i) & 1;
		long r = (right >> i) & 1;
		long s = l ^ r ^ carry;
		carry  = (l & r) | (r & carry) | (l & carry);
		sum = sum | (s << i);
	}
	return sum;
}

//Twos Complement function from my lab 3
long twos (long value){
	return AddInt(~value, 1);	
}

//Multiply function from my lab 3
long mul(long left, long right){

//creates variables for the product, the place, and a temporary left to be added to the product
	long product = 0;
	long place = 0;
	long leftT = 0;

	while (right != 0){
//sets the rightmost bit of the right value as the multiplier bit
		long multiplier = right & 1 ;

//if the multiplier bit is one, the temporary left value is shifted left by the current place and then added to the product
		if(multiplier)
		{
			leftT = left<<place;
			product	 = AddInt (product,leftT);
		}
//the place is incremented and the right is shifted right once so the multiplier bit is the next one along the line
		place  = AddInt (place, 1);
		right = right >> 1;

	}
	return product;
}

