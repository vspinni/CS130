#include <iostream>

#include <fstream>

#include <sstream>

using namespace std;
struct PERSON {
	char name[51];
	int age;
	char gender;
};
extern "C" PERSON * Search(const PERSON people[], int num_people, const char * name, int age, char gender);
extern "C" int Median(const int array[], int array_size, int * buffer);

int main() {
	ifstream read("names");

	if (read.is_open()) {
		int num = 0;
		int p_count = 0;
		string count_s = "";
		getline(read, count_s);
		sscanf(count_s.c_str(), "%d", & p_count);
		PERSON * people = new PERSON[p_count];
		string line = "";
		while (getline(read, line)) {
			if (num % 2 == 1) {
				sscanf(line.c_str(), "%d %c", & people[num / 2].age, & people[num / 2].gender);
			} else {
				unsigned int i = 0;
				for (; i < line.length(); i++) {
					people[num / 2].name[i] = line[i];
				}
				people[num / 2].name[i] = '\0';
			}
			num++;
		}
   cout << "////////////////////////////////////////" << endl << "Part 1 of lab:" << endl << "Contents of array with names read from file \"names\":" << endl;
   for(int i = 0; i< p_count ; i++){
   cout << i << ". " << people[i].name << " " << people[i].age << " " << people[i].gender << endl;
   }
   cout << endl;
		PERSON *person = Search(people, p_count, "Mason Dichloride", 39, 'M');
   cout << "Checking for:  Mason Dichloride 39 M" << endl;
   if(person == nullptr){
     cout << "Result: Person not found" << endl;
   } else{
     cout << "Result: "<< person->name << " " << person->age << " "<<     person->gender << endl;
     }
 	  PERSON *person1 = Search(people, p_count, "Taylor Monetarist", 90, 'M');
       cout << "Checking for:  Taylor Monetarist 90 M"  << endl;
      if(person1 == nullptr){
      cout << "Result: Person not found (this message appears when your function returns nullptr)" << endl;
      }else{
     cout <<"Result: "<<  person1->name << " " << person1->age << " "<< person1->gender << endl;
     }
	} else {
 
		cout << "File \'names\' not found" << endl;
	}
 cout << endl << "////////////////////////////////////////" << endl << "Part 2 of lab: " << endl;
 cout << "Array: 0,10,1,9,2,8,3,7,4,6,5" << endl;
  int arr[] = {0,10,1,9,2,8,3,7,4,6,5};
	int * buffer = new int;
	int median = Median(arr, 11, buffer);
	cout << "Median is: " << median << " (should be 5)" << endl << endl;
 
  cout << "Array: 3,2,1" << endl;
  int arr1[] = {3,2,1};
 	int * buffer1 = new int;
	int median1 = Median(arr1, 3, buffer1);
	cout << "Median is: " << median1 << " (should be 2)" << endl << endl;
 
  cout << "Array: 10,25,29,30,28,2003,129,29,7,10,21,28,25,49,500,129,1024,512" << endl;
  int arr2[] = {10,25,29,30,28,2003,129,29,7,10,21,28,25,49,500,129,1024,512};
	int * buffer2 = new int;
	int median2 = Median(arr2, 18, buffer2);
	cout << "Median is: " << median2 << " (should be 29)" << endl;
	return 0;
}