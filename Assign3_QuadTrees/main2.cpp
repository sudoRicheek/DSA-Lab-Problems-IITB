#include <iostream>
#include "Assign3.h"
#include <queue>

using namespace std;

void printLevelOrder(quad_tree *root)
{
	if (root == nullptr)  return;
	queue<quad_tree *> q;
	q.push(root);

	while (q.empty() == false)
	{
		quad_tree *node = q.front();
		cout << node->size() << " ";
		q.pop();

		if (node->nw != nullptr)
			q.push(node->nw);

		if (node->ne != nullptr)
			q.push(node->ne);

		if (node->se != nullptr)
			q.push(node->se);

		if (node->sw != nullptr)
			q.push(node->sw);
	}
}

int main(int argc, char const *argv[])
{
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);

	int n = 19;
	quad_tree qq(n);
	// qq.set(0, 0, 0, 0, 1);
	// qq.set(1, 1, 1, 1, 1);
	// qq.set(0, 1, 0, 1, 1);
	// qq.set(1, 0, 1, 0, 1);
	qq.resize(3);
	
	qq.set(2, 6, 5, 7, 1);
	qq.set(3, 4, 5, 6, 1);
	qq.set(1, 0, 5, 2, 1);
	// qq.set(0, 2, 1, 7, 1);

	qq.resize(0);
	qq.resize(5);

	// printLevelOrder(&qq);
	// cout << qq.countones() << endl;
	// int x1, x2, y1, y2;
	// cin >> x1 >> x2 >> y1 >> y2;
	// quad_tree qq1(n);
	// qq1.set(x1, y1, x2, y2, 1);
	// cout << "gwie" << endl;
	// quad_tree qq1(qq);

	// qq.resize(0);
	// qq->overlap(qq1);
	// cout << qq.get(1,31) << endl;
	for (int i = 0; i < (1 << qq.size()); ++i) {
		for (int j = 0; j < (1 << qq.size()); ++j)
			std::cout << qq.get(i, j) << " ";
		std::cout << std::endl;
	}


	// if (qq.nw == nullptr)
	// {
	// 	cout << "F" << endl;
	// }
	// if (qq.ne == nullptr)
	// {
	// 	cout << "F" << endl;
	// }
	// if (qq.se == nullptr)
	// {
	// 	cout << "F" << endl;
	// }
	// if (qq.sw == nullptr)
	// {
	// 	cout << "F" << endl;
	// }
	return 0;
}