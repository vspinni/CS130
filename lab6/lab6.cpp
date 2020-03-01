//Lab 6
//Shravan Pinni
//COSC 130
//2/22/19
// Helped David Hu

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

//Checks the arguments
	if(argc < 4){
		printf("Improper inputs");
		return -1;
	}
	 
//initializes variables
	FILE *fin;
	int nkey;
	char dkey = argv[2][0];
	fin = fopen(argv[1], "rb");
	sscanf(argv[3],"%d",&nkey);

//sets seek to end to find total bytes
	fseek(fin, 0, SEEK_END);
	int length = ftell(fin);

//sets seek back to 0
	fseek(fin,0,SEEK_SET);

//the number of chunks is the length divided by the chunk size
	int chunks = length/8;
	
//allocating memory for pointers that store the data and the indexes
	char *data = new char[chunks];
	int *index = new int[chunks];

//gets the data and index from the file and stores them
	for (int i = 0;i<chunks;i++){
		fseek(fin,i*8,SEEK_SET);
		fread(&data[i],1,1,fin);
		fseek(fin,3,SEEK_CUR);
		fread(&index[i],1,4,fin);
	}

//new pointer for output that uses the index as the indexes and the data for the data
	char *output = new char[chunks];

//decodes the data and the indexes
	for(int i = 0;i<chunks;i++){
		data[i] = data[i] ^ dkey;
		index[i] = index[i] ^ nkey;
//checks to see if the decoded indexes are valid
		if(index[i] < 0 || index[i] > chunks){
			printf("Error decoding chunk %d, decoded index -209322571, but max chunks is %d.", i, chunks);
			return -1;
		}
//puts data in the output pointer in the order of the indexes
			output[index[i]] = data[i];
	}

//prints the output array
	for(int i  = 0;i<chunks;i++){
		printf("%c",output[i]);
	}
}
