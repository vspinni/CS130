//For Lab 5
//COSC 130
//Shravan Pinni
//2/8/19
//Did not work with anyone

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <array>

using namespace std;

int main() {
	vector <string> strings;

	string temp;
//Reads file
	printf("Enter file to read.");
	
	ifstream fin;
	char myString[64];	
	scanf("%s",myString);

	fin.open(myString);
//Extracts lines from file using while loop
	while (getline(fin,temp)){
	strings.push_back(temp);
	}

	fin.close();
//Prints out the strings from the vector into the console until the tilde
//and then a new line and new entry
	for (unsigned long i = 0; i < strings.size(); i++){
		if(strings.at(i) =="~")
		printf("%s\n", "\nNew Entry:  ");
		else
		printf ("%s\n", strings.at(i).c_str()); 
	 }
	
return 0;


}

