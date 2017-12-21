//Christian Eaves
//Lab 5
//Program solves sudoku puzzles by using recursion and back-tracking.
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class sudoku {
	public:
		sudoku();

		void solve();

		void read(const char *);
		void write(const char *);
		void write(const char *, const char *);

	private:
		int solve(int, int);

		// various support functions 
		bool unique_value(int, int);
		// error_check_value()
		bool error_check_value();
		// error_check_uniqueness()
		bool error_check_uniqueness();

		void display();

		int game[9][9];
};
//Checks values to make sure they are between 0 and 9
bool sudoku::error_check_value(){
	int err;
	for(int i = 0; i <= 8; i++){
		for(int j = 0; j <= 8; j++){
			if( game[i][j] < 0 || game[i][j] > 9){
				cerr << i << " "  << j << " " << game[i][j] << " illegal grid value" << endl;
				err = 1;
			}
		}
	}
	if(err==1)
		return 1;
	return 0;
}
//Checks to see if the values in a 3x3 grid are unique
bool sudoku::unique_value(int x, int y){
	//Loops through column, checks each row for uniqueness.
	for(int r = 0; r < 9; r++){
		if(r != x) {
			if (game[r][y] == game[x][y]){ return true;}
		}
	}

	//Loops through rows, checks columns for uniqueness
	for(int c = 0; c < 9; c++){
		if(c != y) {
			if(game[x][c] == game[x][y]){ return true;}
		}
	}

	//Checking box for uniqueness
	int sx = x-(x%3);
	int sy = y-(y%3);

	for(int row = sx; row < sx+3; row++){
		for(int col= sy;  col< sy+3 ; col++){
			if(col != y && row != x){
				if(game[row][col] == game[x][y]){ return true;}
			}
		}
	}
	return false;
}
//Checks to see if the puzzle has all unique values
bool sudoku::error_check_uniqueness(){
	int err;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(game[i][j] != 0){
				if(unique_value(i,j)){
					cerr << i << " " << j << " " << game[i][j] << " illegal non-unique value" << endl;
					err = 1;
				}
			}
		}
	}
	if(err==1)
		return 1;
	return 0;
}

sudoku::sudoku() { 
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++)
			game[i][j] = 0;
	}
}

void sudoku::solve() {
	cout << "SOLVE\n";

	// call recursive computation
	solve(0,0);


	display();

	// error checks data values
	if(error_check_value() != 0){
		exit(0);
	}
	// error checks for uniqueness
	if(error_check_uniqueness() != 0){
		exit(0);
	}
}
void sudoku::read(const char *fname) {
	cout << "READ\n";
	int bgrid = 0;
	ifstream fin(fname);

	int i, j, v;

	while (fin >> i >> j >> v) {
		// error checks grid indices
		if((i < 0 || i > 8) || (j < 0 || j > 8)){
			cout << i << " " << j << " " << v << " illegal grid index" << endl;
			bgrid = 1;
		}

		game[i][j] = v;
	}

	fin.close();

	// exit if bad grid indices
	if(bgrid == 1){
		exit(0);
	}

	display();
	// exits if bad values
	if(error_check_value() != 0){
		exit(0);
	}
	// exits if non unique
	if(error_check_uniqueness() != 0){
		exit(0);
	}
}

void sudoku::write(const char *fname) {
	ofstream fout(fname);

	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (0 < game[i][j]) {
				fout << i << " "
					<< j << " "
					<< game[i][j] << "\n";
			}
		}
	}

	fout.close();
}

void sudoku::write(const char *fname, const char *addon) {
	int N1 = strlen(fname);
	int N2 = strlen(addon);

	char *n_fname = new char[N1+N2+2];

	// strip .txt suffix, then concatenate _addon.txt
	strncpy(n_fname, fname, N1-4);
	strcpy(n_fname+N1-4, "_");
	strcpy(n_fname+N1-3, addon);
	strcpy(n_fname+N1-3+N2, ".txt");

	write(n_fname);

	delete [] n_fname;
}

void sudoku::display() {
	cout << "| ----------------------------- |\n";
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (j%3 == 0) 
				cout << "|";
			cout << "  " << game[i][j];
		}
		cout << "  |\n";
		if (i%3 == 2)
			cout << "| ----------------------------- |\n";
	}
}

int sudoku::solve(int i, int j) {
	// if solution found, 
	//   return solution-found
	// set cell index (i,j)
	// determine valid values 
	// if no valid values left,
	//   return road-to-nowhere
	// iterate thru valid values 
	//   game[i][j] = next value
	//   if solve(arguments) == solution-found
	//     return solution-found
	// reset: game[i][j] = 0
	// return road-to-nowhere
	//
	// iterate through table
	while(i<9 && game[i][j] != 0){
		j++;
		if(j==9){
			i++;
			j = 0;
		}
	}
	//if base case; return true
	if(i == 9) return true;

	//iterate through solutions, if found keep solving, otherwise reset element to 0. "we must go deeper"
	for(int x = 1; x <= 9; x++){
		game[i][j] = x;
		if(!unique_value(i,j) && solve(i,j)){
			return true;
		}
	}
	game[i][j] = 0;
	return false;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));

	if ((argc != 3) ||
			(strcmp(argv[1], "-s") != 0) ||
			strstr(argv[argc-1], ".txt") == NULL) {
		cerr << "usage: Sudoku -s game.txt\n";
		exit(0);
	}

	sudoku sudoku_game;

	if (strcmp(argv[1], "-s") == 0) {
		sudoku_game.read(argv[2]);
		sudoku_game.solve();
		sudoku_game.write(argv[2], "solved");
	}
}
