#include <bits/stdc++.h>
using namespace std;

#include <iostream>
#include <random>
#include <limits>

std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
                             //and seed it with entropy.

//Define the distribution, by default it goes from 0 to MAX(unsigned long long)
//or what have you.
std::uniform_int_distribution<unsigned long long> distr;

void dos() {
	cout << 6 << '\n';
	int l = 2+(rand()%19);
	char str[20];
	str[0] = 'a';
	for (int i = 1; i < l; i++) {
		str[i] = 'a'+(rand()%6);
	}
	for (int i = 0; i < l; i++)
		cout << str[i];
	cout << endl;
	for (int i = 0; i < 5; i++) {
		int L = 1+(rand()%20);
		for (int i = 0; i < L; i++){
			str[i] = 'a'+(rand()%6);
			cout << str[i];
		}
		cout << endl;
	}
	cout << 2 << endl;
	cout << 1 << ' ' << (long long)(distr(eng)%((long long)1e18)) << endl;
	cout << 1 << ' ' << (long long)(distr(eng)%((long long)1e18)) << endl;
}

int main() {
	srand(time(NULL));
	cout << 1000 << '\n';
	int t = 1000;
	while (t--)
		dos();
	return 0;
}