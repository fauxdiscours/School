//Christian Eaves
//Prime1, checks to see if user input number is prime.
#include<iostream>
#include<cmath>

using namespace std;
//Checks if number is prime by dividing the number by up to its square root.
bool isprime(int number) {

	int	sroot = sqrt(number);
	//If number < 2 it is not prime because 2 is the smallest prime number
	if(number < 2){
		return false;
	}
	//Checks to see if number is prime, if the remainder is 0 return false, otherwise return true
	for(int i = 2; i <= sroot; i++){
		if((number%i) == 0){ return false; }
	}
	return true;
}

int main()
{
	int number;
//Outputs " is a prime number" after the number if it is prime
	while (cin >> number ) {
		if (isprime(number))
			cout << number << " is a prime number" << endl;

	}
	return 0;
}
