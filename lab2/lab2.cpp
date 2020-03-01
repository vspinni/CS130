//Lab 2b
//COSC 130
//Shravan Pinni
//1/18/19
//Did not work with anyone

#include <cstdio>
#include <string>
#include <vector>


using namespace std;

//Declaration of BITSET class and creation of prototypes
class BITSET{
	vector <int> bits;

	public:
		BITSET();
		bool Test(int index);
		void Set(int index);
		void Clear (int index);
		string to_binary(int number);

};


int main(){

	//takes in character command and bit number
	char command;
	int bit;
	BITSET data;
	printf ("%s\n", "Please enter a character command and a bit");
	scanf("%c\n", &command);
	scanf("%d\n", &bit);
	
	//uses while loop to keep user in switch statement until q is entered
	while (command !='q'){

		//used to sort between the different inputs
		switch(command){
			
			case 't': 
				data.Test(bit);
				break;
			case 's':
				data.Set(bit);
				break;
			case 'c':
				data.Clear(bit);
				break;
			case 'p':
				printf("%s\n", data.to_binary(bit).c_str());
				break;
			case 'q':
				break;
			default: 
				break;
		}
		printf("%s\n", "Please enter a character command and a bit");
		scanf("%c\n", &command);
		scanf("%d\n", &bit);
	}	
	
	return 0;
}

//default constructor for BITSET
BITSET:: BITSET(){
	bits.resize(1,0); 
}

//Test function for BITSET
bool BITSET:: Test(int index){
//finds out set and index using division and modulus
	int set = index/32;;
	int smallIndex = index;
	
	//accounts for the set not existing
	if (set > (int)(bits.size()-1)){
		return 0;
		}
//returns true or false based on bit in index given
	if(index > 31){
		smallIndex = index% 32;
	}
	return (bits.at(set)>>smallIndex) & 1;
}

//Set function for BITSET
void BITSET:: Set(int index){
	// finds out index and set using division and modulus
	int set =index/32;
	int smallIndex = index;

	// creates a new set if the current one isnt large enough
	if(set > (int)bits.size()){
		smallIndex = index%32;
		for (int i=0;i <(int)(set-bits.size());i++){
			bits.push_back(0);
		}
	}
	//changes the value of the bit to 1
	bits.at(set) = bits.at(set) | (1<<smallIndex); 
}

//Clear function for BITSET
void BITSET:: Clear(int index){
	//finds index and set using modulus and division
	int set = index/32;
	int smallIndex = index%32;
	//changes bit at given index to 0
	if((int)(bits.size()-1) >= set)
	bits.at(set) = bits.at(set) & ~(1<<smallIndex);
	
	//if a set is empty, deletes set
	if((bits.at(set)==0)&& (set>0))
		bits.resize(set-1);
}

//BITSET function to_binary
string BITSET:: to_binary(int number){
	string output;
	//indexMax and indexMin puts the entire given set into the form of indexes for the entire vector
	int indexMax = (number+1)*31;
	int indexMin = number*31;

	//returns an empty set if the number given is greater than the number of sets
	if(number > (int)(bits.size()-1)){
		return " ";
	}else {
		//manually enters every bit in the set as a string
		for (int i = indexMax;i>indexMin;i--){
			output += Test(i);
			//inserts spaces in the string every 4 bits printed
			if(i%4 ==3)
			output +=" ";	
		}
		return output;
	}	
}

