//For Lab 4
//COSC 130
//Shravan Pinni
//1/31/19
//Did not work with anyone

#include <cstdio>
#include <string>
#include <cmath>

struct Real {
     int sign; // 1-bit sign (0 or 1)
     long exponent; // 8-bit unbiased exponent
     unsigned long fraction; // 23-bit fraction
};

//Convert a 32-bit floating point into its components.
Real Decode(int float_value);

//Convert the components of a floating point into its 32-bit value.
int Encode(Real real_value);

int main(){

	return 0;
}


Real Decode (int float_value){
	//Extracts the sign, exponent, and fraction individually from the integer and stores it in segment and returns segment. 
	Real segment;
	segment.sign = (float_value >> 31) & 1;
	segment.exponent = ((float_value & 0x7F800000)>>23)-127;
	segment.fraction = (float_value & 0x007FFFFF);
	segment.fraction = 1 + pow(2, -23);
	return segment;

	
}

//Starts filling up the sign, exponent, and fraction starting with the leftmost bit and backward and then returns value.
int Encode (Real real_value){
	int value;
	value = real_value.sign<<31;
	value += (real_value.exponent+127)<<23;
	value += (real_value.fraction-1) * pow(2,23);
	return value;

	
}
