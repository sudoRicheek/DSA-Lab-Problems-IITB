#include <bits/stdc++.h>
using namespace std;

void f1(int x) {
	string ss[50];
	ss[0] = "a";
	for (int i = 1; i <= 30; i++) {
		string s2 = "";
		for (char c : ss[i-1]) {
			if (c == 'a')
				s2 += "ab";
			else if (c == 'b') s2 += "a";
		}
		ss[i] = s2;
	}
	while (x){
		int ind = 1+(rand()%30);
		int length = 1+(rand()%ss[ind].length());
		if (length + 1000 <= ss[ind].length()){
			cout << 2 << ' ' << ss[ind].substr(length,1000) << '\n';
			x--;
		}
	}
	/*string xs = ss[29].substr(7665,1000);
	for (int i = 0; i < ss[16].length() - xs.length(); i++) {
		if (ss[16].substr(i,xs.length()) == xs)
			cout << "YES" << endl;
	}*/
}

void f2(int x) {
	string ss[50];
	ss[0] = "a";
	for (int i = 1; i <= 15; i++) {
		string s2 = "";
		for (char c : ss[i-1]) {
			if (c == 'a')
				s2 += "ab";
			else if (c == 'b') s2 += "ba";
		}
		ss[i] = s2;
	}
	while (x){
		int ind = 1+(rand()%15);
		int length = 1+(rand()%ss[ind].length());
		if (length + 1000 <= ss[ind].length()){
			cout << 2 << ' ' << ss[ind].substr(length,1000) << '\n';
			x--;
		}
	}
	/*string xs = ss[15].substr(7665,1000);
	for (int i = 0; i < ss[11].length() - xs.length(); i++) {
		if (ss[11].substr(i,xs.length()) == xs)
			cout << "YES" << endl;
	}*/
}

void f3(int x) {
	string ss[1000];
	ss[0] = "a";
	for (int i = 1; i <= 1000; i++) {
		string s2 = "";
		for (char c : ss[i-1]) {
			if (c == 'a')
				s2 += "ab";
			else if (c == 'b') s2 += "a";
			else if (c == 'c') s2 += "d";
			else if (c == 'd') s2 += "c";
		}
		ss[i] = s2;
	}
	while (x){		
		int ind = 1+(rand()%1000);
		int length = 1+(rand()%ss[ind].length());
		if (length + 50 <= ss[ind].length()){
			cout << 2 << ' ' << ss[ind].substr(length,50) << '\n';
			x--;
		}
	}
	/*string xs = ss[15].substr(7665,1000);
	for (int i = 0; i < ss[11].length() - xs.length(); i++) {
		if (ss[11].substr(i,xs.length()) == xs)
			cout << "YES" << endl;
	}*/
}

int main() {
	srand(time(NULL));
	int x = 100;
	cout << "2\n";
	cout << "ab\n";
	cout << "ba\n";
	cout << x << '\n';
	f2(x);
	return 0;
}