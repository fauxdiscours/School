/* Christian Eaves
 * CS140
 * Program encodes and decodes strings using command line args */
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;

//function declarations

void encode(string&, int);
void decode(string&, int);

int main(int argc, char* argv[]){
	string str;
	//Error checking: 3 arguments, -encode/-decode commands only, 0-9 only
	if(argc != 3){
		cerr << "Usage: -encode/-decode 0-9" << endl;
		return 1;
	}
	if(strcmp(argv[1], "-encode") != 0 && strcmp(argv[1], "-decode") != 0){
		cerr << "case 1 Usage: -encode/-decode 0-9" << endl;
		return 1;
	}
	if(isdigit(argv[2][0]) != 1){
		cerr << "Usage: -encode/-decode 0-9" << endl;
		return 1;
	}

	//Reading in the strings
	getline(cin,str);
	if(strcmp(argv[1], "-encode") == 0){
		encode(str, atoi(argv[2]));
	}
	if(strcmp(argv[1], "-decode") == 0){
		decode(str, atoi(argv[2]));
	}
	return 0;
}
//Function to encode given string
void encode(string &str,int shift){
	//Uses built-in functions to check if letters are uppercase, lowercase, or alpha and then adds the shift to them.
	for(int i = 0; i < str.length(); i++){
	if(isalpha(str[i])){

			if(islower(str[i])){
				str[i] += shift;
				
				if(islower(str[i]) == 0)
					str[i] -= 26;

			}else if(isupper(str[i])){

				str[i] += shift;

				if(isupper(str[i]) == 0)
					str[i] -= 26;
			}
		}
		cout << str[i];
	}
	cout << endl;
}
//Function to decode given string
void decode(string &str, int shift){
	//Uses built-in functions to check if letters are uppercase, lowercase, or alpha and then subtracts the shift from them.
	for(int i = 0; i < str.length(); i++){
		if(isalpha(str[i])){

			if(islower(str[i])){
				str[i] -= shift;

				if(islower(str[i]) == 0)
					str[i] += 26;
			}else if(isupper(str[i])){

				str[i] -= shift;

				if(isupper(str[i]) == 0)
					str[i] += 26;
			}
		}
		cout << str[i];
	}
	cout << endl;
}
