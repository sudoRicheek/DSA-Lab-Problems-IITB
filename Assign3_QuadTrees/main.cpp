#include<bits/stdc++.h>
#include "Assign3.h"
#include<chrono>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<quad_tree> Q (2, quad_tree(n));
	int t;
	cin >> t;
	int count = 0;
	double setduration = 0, getduration = 0, orduration = 0, andduration = 0, complementduration = 0, resizeduration = 0, extractduration = 0;
	while (t--) {
		char c;
		cin >> c;
		switch (c) {
		case 'S':
		{
			int id;
			int x1, y1, x2, y2;
			bool b;
			cin >> id >> x1 >> y1 >> x2 >> y2 >> b;
			auto t1 = chrono::high_resolution_clock::now();
			Q[id].set(x1, y1, x2, y2, b);
			auto t2 = chrono::high_resolution_clock::now();
			setduration += chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			cout << 'S' << count++ << endl;
			break;
		}
		case 'G':
		{
			int x, y, id;
			cin >> id >> x >> y;
			auto t1 = chrono::high_resolution_clock::now();
			cout << Q[id].get(x, y) << endl;
			auto t2 = chrono::high_resolution_clock::now();
			getduration += chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			cout << 'G' << count++ << endl;
			break;
		}
		case 'O':
		{
			int id;
			cin >> id;
			auto t1 = chrono::high_resolution_clock::now();
			Q[id].overlap(Q[(id + 1) % 2]);
			auto t2 = chrono::high_resolution_clock::now();
			orduration += chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			cout << 'O' << count++ << endl;
			break;
		}
		case 'I':
		{
			int id;
			cin >> id;
			auto t1 = chrono::high_resolution_clock::now();
			Q[id].intersect(Q[(id + 1) % 2]);
			auto t2 = chrono::high_resolution_clock::now();
			andduration += chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			cout << 'I' << count++ << endl;
			break;
		}
		case 'C':
		{
			int id;
			cin >> id;
			auto t1 = chrono::high_resolution_clock::now();
			Q[id].complement();
			auto t2 = chrono::high_resolution_clock::now();
			complementduration += chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			cout << 'C' << count++ << endl;
			break;
		}
		case 'R':
		{
			int m;
			cin >> m;
			auto t1 = chrono::high_resolution_clock::now();
			Q[0].resize(m);
			Q[1].resize(m);
			auto t2 = chrono::high_resolution_clock::now();
			resizeduration += chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			cout << 'R' << count++ << endl;
			break;
		}
		case 'E':
		{
			int x, y, m;
			cin >> x >> y >> m;
			cout << 'E' << count++ << endl;
			// auto t1 = chrono::high_resolution_clock::now();
			// Q[0].extract(x,y,m);
			// Q[1].extract(x,y,m);
			// auto t2 = chrono::high_resolution_clock::now();
			// extractduration += chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
			break;
		}
		}
	}
	cout << "Completion" << endl;
	cout << setduration << endl;
	cout << getduration << endl;
	cout << orduration << endl;
	cout << andduration << endl;
	cout << complementduration << endl;
	cout << resizeduration << endl;
	cout << extractduration << endl;
}