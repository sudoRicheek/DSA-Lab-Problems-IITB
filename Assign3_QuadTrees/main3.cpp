#include "Assign3.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n = 3;
	int x1, y1, x2, y2;
	// cin >> x1 >> x2 >> y1 >> y2;
	quad_tree qq(n);
	// qq.set(x1, y1, x2, y2, 1);

	quad_tree qq1(n);
	qq1.set(2, 0, 5, 7, 1);

	// quad_tree *qq2 = new quad_tree(qq);

	// qq.intersect(qq1);
	qq.complement();
	qq.set(0, 0, 3, 3, 0);
	qq.set(2, 3, 7, 6, 0);




	// cout << qq.get(1, 1) << endl;
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 0; j < (1 << n); ++j)
			cout << qq.get(i, j) << " " << flush;
		cout << endl;
	}
	cout << endl;
	qq.intersect(qq1);
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 0; j < (1 << n); ++j)
			cout << qq1.get(i, j) << " " << flush;
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 0; j < (1 << n); ++j)
			cout << qq.get(i, j) << " " << flush;
		cout << endl;
	}
	// cout << qq.countones() << endl;
	// qq.resize(2);
	// for (int i = 0; i < (1 << 2); ++i) {
	// 	for (int j = 0; j < (1 << 2); ++j)
	// 		cout << qq.get(i, j) << " " << flush;
	// 	cout << endl;
	// }

	return 0;
}