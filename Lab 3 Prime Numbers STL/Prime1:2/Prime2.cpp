//Christian Eaves
//Prime2, uses vectors to store a list of prime numbers 
#include<vector>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

class isprime {
	public:
		isprime() { primes.push_back(2);  }
		bool operator()(int);
		bool prime(int);
		//Creates a private vector named primes
	private:
		void psh(int);
		vector<int> primes;
};
//Calculates prime numbers and returns true if the number is prime, false elsewise.
bool isprime::operator()(int number){
	//if primes.back() < number {fill list}
	if(primes.back() <  number){
		psh(number);
	}
	//If primes.back() > number find the number in the list.
	vector<int>::iterator it;
	it = find(primes.begin(), primes.end(), number);
	if(it !=primes.end()){
		return true;
	}else{
		return false;
	}
}

void isprime::psh(int number){
//If the number is prime, add all prime numbers from primes.back() to number into the list. 
	if(prime(number)){
		int i = primes.back() + 1;
		while(1){
			if(prime(i)){
				primes.push_back(i);
			}
			i++;
			if(primes.back() > number)
				break;
		}
	}
}
bool isprime::prime(int number){
	//Computes prime numbers.
	int sroot = sqrt(number);
	for(int i = 2; i <= sroot; i++){
		if((number%i) == 0)
			return false;
	}
	return true;
}

int main(){
	isprime pcheck;
	int number;
	//Loops through inputs, checks if number is prime, if true outputs number is a prime numbers
	while (cin >> number ) {
		if (pcheck(number))
			cout << number << " is a prime number" << endl;
	}
}
