#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <iostream>
#include <cstddef>
using namespace std;

class permutation
{
	int len;
	int* perm;
public:
	permutation();
	permutation(permutation const &obj);
	permutation(int n, int a[]);
	~permutation();

	permutation const operator=(permutation const &q);
	int size() const;
	int* to_array() const;
	permutation const operator-() const;
	permutation const operator*(permutation const &q) const;
	permutation const square_root() const;
};
#endif
