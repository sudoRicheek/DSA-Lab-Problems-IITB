#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <iostream>
#include <cstddef>
using namespace std;

class permutation
{
	int len;
	int* perm;
	long long int gcd(long long int a, long long int b) const;
	long long int lcm(long long int a, long long int b) const;
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
	// permutation const naivepower(long long int i) const;
	permutation const operator^(long long int n) const;
	bool is_power(permutation const &q) const;
	int log(permutation const &q) const;
};
#endif
