#include "Assign3.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n = 1;

	quad_tree qq(1);
	qq.set(0, 0, 0, 0, 1);
	qq.set(1, 1, 1, 1, 1);

	quad_tree qq1(1);
	qq1.set(1, 0, 1, 0, 1);
	qq1.set(0, 1, 0, 1, 1);

	qq.intersect(qq1);

	cout << qq.sizen << endl;
	if (qq.nw == nullptr)
	{
		cout << "yo bitch" << endl;
	}
	else
	{
		cout << qq.nw->sizen << endl;
	}
	for (int i = 0; i < (1 << n); ++i) {
		for (int j = 0; j < (1 << n); ++j)
			cout << qq.get(i, j) << " " << flush;
		cout << endl;
	}

	return 0;
}