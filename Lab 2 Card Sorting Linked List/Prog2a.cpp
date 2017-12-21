#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
	"8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };

string random_card(bool verbose=false) {
	string card;

	card = face[ rand()%13 ];
	card += " of ";
	card += suit[ rand()%4 ];

	if (verbose)
		cout << card << "\n";

	return card;
}

int main(int argc, char *argv[])
{
	bool verbose = false;
	int seedvalue = 0;

	for (int i=1; i<argc; i++) {
		string option = argv[i];
		if (option.compare(0,6,"-seed=") == 0) {
			seedvalue = atoi(&argv[i][6]);
		} else if (option.compare("-verbose") == 0) {
			verbose = true;
		} else 
			cout << "option " << argv[i] << " ignored\n";
	}

	srand(seedvalue);

	// declare a table called deck that keeps track of
	// card faces dealt for each suit -- initialize to 0

	int deck[4][13] = {0};
	int s = 0;
	while (1) {
		string card = random_card(verbose);

		// reverse engineer card suit and face
		stringstream table;

		table << card;

		string Tface;
		string trash;
		string Tsuit;
		//Read in face and suit
		table >> Tface >> trash >> Tsuit;
		//Iterate the array at the values where the face and suit match the array index
		for(int x = 0; x < 4; x++){
			for(int y = 0; y < 13; y++){
				if(Tsuit == suit[x] && Tface == face[y]){
					deck[x][y]++;						
					s = x;
				}

			}
		}



		int leave = 0;
		// break out of loop if stopping criteria met
		if(deck[s][10] > 0  && deck[s][11] > 0 && deck[s][12] > 0){
			leave = 1;
		}
		if(leave == 1)
			break;
	}
	// print formatted table contents to stdout
	// formatting output table with setw and right
	cout << setw(11) << "Clubs : ";
	for (int j = 0; j < 13; j++){
		cout << setw(4) << right << deck[0][j] << " ";
	}
	//if s = clubs, mark.
	if(s==0){
		cout << "**";
	}
	cout << endl;

	cout << setw(11) << "Diamonds : ";
	for(int j = 0; j < 13; j++){
		cout << setw(4) << right << deck[1][j] << " ";
	}
	if(s==1){
		cout << "**";
	}
	cout << endl;

	cout << setw(11) << "Hearts : ";
	for(int j = 0; j < 13; j++){
		cout << setw(4) << right << deck[2][j] << " ";
	}
	if(s==2){
		cout << "**";
	}
	cout << endl;

	cout << setw(11) << "Spades : ";
	for(int j = 0; j < 13; j++){
		cout << setw(4) << right << deck[3][j] << " ";
	}
	if(s==3){
		cout << "**";
	}
	cout << endl;
}



