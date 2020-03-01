//Lab 5
//Shravan Pinni
//COSC 130
//2/15/19
//Worked with no one

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Room struct with a string for title and description
struct Room{
    string title;
	string description;
//used int as a boolean for each direction
	int north = 0;
	int south = 0;
	int east = 0;
	int west = 0;
//variables for the room numbers that the exits connect to
	int n = 0;
	int s = 0;
	int e = 0;
	int w = 0;
};

int main (int argc, char *argv[]){

//checks to see if args are the proper number
	if (argc < 2) {
		printf("Usage: %s <roomfile>", argv[0]);
		return -1;
	}

//a file stream for each while loop
	ifstream fin1,fin2;
	stringstream ss;
	string line = "";
	int inroom = 0;
	char command = '0';
	int tildetotal;
	int rmct = -1;
	int totalrms =0;
	int tildes = 0;

//opens file
	fin1.open(argv[1]); 
//counts the number of tildes
	while(getline(fin1, line)){
		if(line == "~")
			tildetotal++;
	}
//closes file stream
	fin1.close();
//finds the total number of rooms based on tildes and makes a pointer with that length
	totalrms = tildetotal / 3;

	Room *rooms = new Room[totalrms+1];

//reopens the file to extract the information
	fin2.open(argv[1]);
	while(getline(fin2, line)){

//counts tildes currently
		if (line == "~"){
			tildes++;	
		}
//uses the number to tildes to determine whether each line is a description, title, or exits
		else {
//since 3 tildes indicates a new room, rmct goes up and the title is extracted into the new one
			if(tildes % 3 == 0){
				rmct++;
				rooms[rmct].title = line;
		
			}
//extracts the description if the mod of the tilde count is 1
			if (tildes % 3 == 1){
				rooms[rmct].description +=line;
			}
//extracts the directions using a string stream and then puts the direction itself and the room number into different variables
			if(tildes%3 == 2){
				stringstream ss(line);
				char direction;
				ss >> direction;
//switch statement to check each direction
				switch(direction){
					case 'n':{
						rooms[rmct].north = 1;
						ss >> rooms[rmct].n;
						break;
						}
					case 's':{
						rooms[rmct].south = 1;
						ss >> rooms[rmct].s;
						break;
						}
					case 'w':{
						rooms[rmct].west = 1;
						ss >> rooms[rmct].w;	
						break;
						}
					default:{
						rooms[rmct].east = 1;
						ss >> rooms[rmct].e;			
						break;
						}				
				}
			}
		}	
	}
//closes file stream
	fin2.close();

//while loop for the game itself
	while(command != 'q')
	{
//prints the title, description and exit locations when l is pressed
		if(command =='l'){
			printf("%s\n",rooms[inroom].title.c_str());
			printf("%s\n",rooms[inroom].description.c_str());
//goes through and checks each potential exit direction
			printf("Exits: \n");
			if(rooms[inroom].north){
				printf("n ");
			}
			if(rooms[inroom].south){
				printf("s ");
			}
			if(rooms[inroom].east){
				printf("e ");
			}
			if(rooms[inroom].west){
				printf("w ");
			}
			printf("\n");

		}
// else for n that goes over both an exit being and not being north
		else if(command == 'n'){	
			if(rooms[inroom].north){
				printf("You moved NORTH.\n");
				inroom = rooms[inroom].n;
			}
			else{
				printf("You can't go NORTH.\n");
			}
		}
// else for s that goes over both an exit being and not being south
		else if(command == 's'){
			if(rooms[inroom].south){
				printf("You moved SOUTH.\n");
				inroom = rooms[inroom].s;
			}
			else{
				printf("You can't go SOUTH.\n");
			}
		}

// else for e that goes over both an exit being and not being east
		else if(command == 'e'){
 			if(rooms[inroom].east){
				printf("You moved EAST.\n");
				inroom = rooms[inroom].e;
			}
			else{
				printf("You can't go EAST.\n");
			}  
		}
// else for w that goes over both an exit being and not being west
		else if(command == 'w'){
			if(rooms[inroom].west){
				printf("You moved WEST.\n");
				inroom = rooms[inroom].w;
			}
			else{
				printf("You can't go WEST.\n");
			}
		}
// does nothing for case q or anthing else
		else if(command == 'q'){
		
		}
		else {				
		}
//asks for an input again
	printf("%c",'>');
	printf(" ");
	scanf(" %c", &command);
	} 
//gives memory back to hard drive
	delete [] rooms;
	return 0;

}

