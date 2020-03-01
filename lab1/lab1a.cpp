//Lab 1A
//COSC130
//This lab had us design 4 functions that converted back and forth from char to int and string to int
//Shravan Pinni
//1/11/19
//None

#include <iostream>
#include <string>
using namespace std;

//Prototypes for the functions that you will write
int  CharToInt(char v);
char IntToChar(int v);
int StringToInt(string val);
string IntToString(int val);

int main(int argc, char *argv[])
{
        string sresult;
        int left;
        int right;
        char op;

        if (4 != argc) {
                printf("Usage: %s <left> <op> <right>\n", argv[0]);
                return -1;
        }
        //Notice that this calls your StringToInt. So, make sure you debug
        //StringToInt() to make sure that left and right get a proper
        //value.
        left = StringToInt(argv[1]);
        right = StringToInt(argv[3]);
        op = argv[2][0];
        //Calculate based on the op. Notice that this calls IntToString,
        //so debug your IntToString() function to make sure that sresult
        //is given the proper result. This assumes your StringToInt already
        //works.
        switch (op)
        {
                case 'x':
                        sresult = IntToString(left * right);
                        break;
                case '/':
                        sresult = IntToString(left / right);
                        break;
                case '+':
                        sresult = IntToString(left + right);
                        break;
                case '-':
                        sresult = IntToString(left - right);
                        break;
                case '%':
                        sresult = IntToString(left % right);
                        break;
                default:
                        sresult = IntToString(left);
                        break;
        }

        //Remember, printf is the only output function you may use for this lab!
        //The format string is %d %c %d = %s. This means that the first argument
        //is %d (decimal / integer), %c (character), %d (decimal /integer),
        //%s (string). Notice that because printf() is a C-style function, you
        //must pass strings as character arrays. We can convert a C++ string
        //to a character array (C-style string) by using the c_str() member function.
        printf("%d %c %d = %s\n", left, op, right, sresult.c_str());
        return 0;
}


//This function converts from Int to Char. It just subtracts '0' from the ASCII table from the given char and makes it an int
int CharToInt(char v){
	int i = v-'0';
	return i;
}

//This function converts from Char to Int. It just adds '0' from the ASCII table to the given int and makes it a char
char IntToChar(int v){
	
	char i = v+'0';
	return i;	
}

// This function converts from String to int
int StringToInt(string val){
	int len = val.length();
	int rVal = 0;

// This section takes care of potential negatives
	int neg = 1;
	if (val[0] == '-'){
		neg = -1;

// A for loop is used here to get each index of the string
		for (int i = 1;i<len;i++){
			int temp = CharToInt(val[i]);
// The nested for loop puts each digit in its proper place
			for (int j = len-1-i;j>0;j--){
				temp *=10;
			}
			rVal+=temp;
			temp = 0;
		}
	}
//This section is for positive inputs
	else {
// Same reason as the first for loop from above
		for (int i = 0;i<len;i++){
			int temp = CharToInt(val[i]);
			
// Same reason as the nested for loop from above
			for (int j = len-1-i;j>0;j--){
				temp*=10;
			}
			rVal+=temp;
			temp = 0;
			}	
	}
// Adds the negative again if the initial String had a negative
	return rVal*neg;
}

string IntToString(int val){
	
	int cVal, neg;
	string rString, tString;
	cVal = val;
	neg = 0;
	char temp;

// Temporarily takes out the negative if it is there
	if(val<0){
		neg =1;
		cVal*=-1;
	}

// Uses mod and division operators to make a the Int a String, except in reverse order
	while (cVal>0){
		temp = (cVal%10)+'0';
		cVal/=10;
		tString +=temp;
		temp = 0;
	}
// Re-adds the negative if it was originally there
	if (neg==1)
		rString = '-';
//Reverses the order of the temporary string so it matches the inputted integer
	for(int i = tString.length()-1;i>=0;i--){
		rString += tString[i];
	}
//This gives a return value in case the input is a zero
	if (val==0)
		rString =IntToChar(val);
	return rString;

}
