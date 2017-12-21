//Christian Eaves
//Lab 4: Hashtables
//Program keeps up with words in ascii files using a hashtable.
//Using 1 grace day
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<ctype.h>
#include<iterator>
using namespace std;

typedef unsigned int uint;

class hash_table {
	public:

		struct key_line {
			string word;
			vector<int> line;
			bool inuse();
			bool operator==(const string &str) { return (str == word); }
		};

		hash_table();
		void insert(const string &, int);
		const vector<int>& find(const string &);
	private: 
		int hash(const string &);
		int nextprime(int);
		int qprobe(const string &);
		void resize();

		int num_inuse;
		int max_inuse;

		vector<key_line> table;
};
//Checks if the line is in use or not
bool hash_table::key_line::inuse(){
	if(word.empty()) { return false; }
	return true;
}

hash_table::hash_table(){
	int N = 23;
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2; // quadratic probe max value
}
//Inserts a string into the hashtable and keep up with the line number
void hash_table::insert(const string & key, int num) {
	int index = qprobe(key);

	if(table[index].inuse() == false){
		table[index].word = key;
		table[index].line.push_back(num);
		if(++num_inuse >= max_inuse){
			resize();
		}
	}else if(table[index].line.end() == std::find(table[index].line.begin(),table[index].line.end(),num)){
		table[index].line.push_back(num);	
	}
}
//Finds the line using the qprobe of the key.
const vector<int>& hash_table::find(const string & key){
	int index = qprobe(key);
	return table[index].line;
}



int hash_table::hash(const string & key) {
	int index = 0;
	const char *c = key.c_str();

	while(*c)
		index = ((index << 5) | (index >> 27)) + *c++;

	return index % table.size();
}
//Finds next prime number
int hash_table::nextprime(int N){
	int i = 2;
	while (i*i <= N) {
		if (N%i == 0) {N++; i = 1; }
		i++;
	}

	return max(3,N);
}
//Quadratic probing
int hash_table::qprobe(const string & key) {
	int index = hash(key);

	int k = 0;
	while (table[index].inuse() && table[index].word != key) {
		index +=2*(++k) -1;
		index = index % table.size();
	}

	return index;
}
//Resizes hash table
void hash_table::resize() {
	vector<key_line> tmp_table;
	string tmp;
	for(int i = 0; i < (int)table.size(); i++){
		if(table[i].inuse() == true)
			tmp_table.push_back(table[i]);
	}

	int N = nextprime(2*table.size());
	table.assign(N, key_line());

	num_inuse = 0;
	max_inuse = N/2;

	for(int i = 0; i < (int)tmp_table.size(); i++) {
		tmp = tmp_table[i].word;
		table [ qprobe(tmp) ] = tmp_table[i];
		num_inuse++;
	}
}

//Main
int main(int argc, char *argv[])
{
	int q = 1;
	hash_table H;
	//Checking to see if text file was provided
	if(argc != 2){
		cerr << "usage: ./hashtable textfile" << endl;
		return 1;
	}
	vector<string> textline;
	//Reading text file, replacing punctuation with spaces, parsing string into words.
	string::iterator it;
	ifstream text;
	text.open(argv[1]);
	if(text.fail()){
		cerr << "usage: ./hashtable textfile" << endl;
		return -1;
	}

	string textln, words;
	vector<string>loc;
	while(getline(text,textln)){
		textline.push_back(textln);
		loc.push_back(textln);
		for(it = textline[q-1].begin(); it != textline[q-1].end(); it++ ){
			if(ispunct(*it))
				*it = ' ';
		}
		stringstream ss;
		ss.str(textline[q-1]);
		while(ss >> words){
			H.insert(words,q);
		}
		ss.clear();
		q++;
	}
	text.close();
	//Prompt find, search vectors
	string s;
	vector<int> found;
	cout << "find> ";
	while(cin >> s){
		found = H.find(s);
		for(int i = 0; i < found.size(); i++){
			cout << found[i] << ": " << loc[found[i]-1] << endl;
		}
		cout << "find> ";
	}
}
