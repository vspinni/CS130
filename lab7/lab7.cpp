//Lab 7 C++ version

#include <string>
#include <cstdio>

int main (int argc, char* argv[]){
	
	int left = 0;
	int right = 0;
	char operation;
	sscanf(argv[1], "%d", &left);
	sscanf(argv[2], "%d", &operation);
	sscanf(argv[3], "%d", &right);
	
	if(operation == "+"){
		cout << "Result:" << argv[1]<< argv[2] << argv[3] << " = "<<  right + left;
	}

	if(operation == "*"){
		return right * left;
	}
	if(operation == "-"){
		return right - left;
	}
	if(operation == "/"){
		return right / left;
	}
	if(operation == '%'){
		return right % left;
	}		
}


