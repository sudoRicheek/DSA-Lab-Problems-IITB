#include "Assign1.h"

typedef long long int lli;
const int MOD = 1e9 + 7;


permutation::permutation() //checked
{
	len = 0;
	perm = NULL;
}

permutation::permutation(permutation const &obj) //checked
{
	this->perm = new int[obj.size()];
	this->len = obj.size();
	for (int i = 0; i < obj.size(); ++i)
		*(this->perm + i) = *(obj.to_array() + i);
}

permutation::permutation(int n, int a[]) //checked
{
	this->perm = new int[n];
	this->len = n;
	for (int i = 0; i < n; ++i)
		*(this->perm + i) = a[i];
}

permutation::~permutation()
{
	if (perm)
	{
		delete[] perm;
		perm = NULL;
	}
}

permutation const permutation::operator=(permutation const&q) //checked
{
	if (this->len == q.size())
	{
		int* arrtemp = q.to_array();
		for (int i = 0; i < q.size(); ++i)
			*(this->perm + i) = *(arrtemp + i);
		return *this;
	}
	this->len = q.size();
	this->perm = new int[this->len];
	int* arrtemp = q.to_array();
	for (int i = 0; i < q.size(); ++i)
		*(this->perm + i) = *(arrtemp + i);

	return *this;
}

int permutation::size() const //checked
{
	return this->len;
}

int* permutation::to_array() const //checked
{
	int* ret_arr = new int[this->len];
	for (int i = 0; i < this->len; ++i)
		*(ret_arr + i) = *(this->perm + i);

	return ret_arr;
}

permutation const permutation::operator-() const //checked
{
	int inv[this->len];
	for (int i = 0; i < this->len; ++i)
		inv[*(this->perm + i)] = i;

	permutation pnew(this->len, inv);
	return pnew;
}

permutation const permutation::operator*(permutation const &q) const
{
	int* comp_arr = new int[q.size()];
	for (int i = 0; i < q.size(); ++i)
		*(comp_arr + i) = *(this->perm + * (q.to_array() + i));

	permutation newptr(q.size(), comp_arr);
	return newptr;
}

permutation const permutation::square_root() const
{
	int* p, *q, *cnt;
	p = new int[103];
	q = new int[103];
	cnt = new int[103];

	for (int i = 0; i < this->len; ++i)
		*(p + i) = *(this->perm + i);

	for (int i = 0; i < 103; ++i)
		*(cnt + i) = -1;

	bool visited[103];
	for (int i = 0; i < 103; ++i)
		visited[i] = false;

	for (int i = 0; i < this->len; ++i)
	{
		if (!visited[i])
		{
			int sz = 0, j = i;
			do {
				visited[j] = 1;
				++sz;
				j = *(p + j);
			} while (j != i);

			if (sz % 2 == 1)
			{
				int k = i;
				for (int j = 0; j < sz / 2 + 1; ++j)
					k = *(p + k);
				do {
					*(q + j) = k;
					k = *(p + k);
					j = *(p + j);
				} while (j != i);
			}
			else if (*(cnt + sz) == -1)
			{
				*(cnt + sz) = i;
			}
			else
			{
				int k = *(cnt + sz);
				do {
					*(q + j) = k;
					j = *(p + j);
					*(q + k) = j;
					k = *(p + k);
				} while (j != i);
				*(cnt + sz) = -1;
			}
		}
	}

	bool flag = true;
	for (int i = 0; i < this->len; ++i)
		if (*(cnt + i) != -1)
		{
			flag = false;
			break;
		}

	int* arrtemp = new int[this->len];
	if (flag)
		for (int i = 0; i < this->len; ++i)
			*(arrtemp + i) = *(q + i);
	else
		for (int i = 0; i < this->len; ++i)
			*(arrtemp + i) = i;

	permutation pnew(this->len, arrtemp);
	return pnew;
}


lli permutation::gcd(lli a, lli b) const {
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

lli permutation::lcm(lli a, lli b) const {
	return (a * b) / gcd(a, b);
}


// permutation const permutation::naivepower(long long int i) const
// {
// 	permutation p3 = *this;
// 	for (int j = 1; j < i; ++j)
// 		p3 = p3 * (*this);

// 	return p3;
// }

permutation const permutation::operator^(long long int n) const // basic checked
{
	bool visited[103];
	for (int i = 0; i < 103; ++i)
		visited[i] = false;

	lli lcm_continuous = 1;
	for (int i = 0; i < this->len; ++i)
	{
		if (!visited[i])
		{
			lli sz = 0, j = i;
			do {
				visited[j] = 1;
				++sz;
				j = *(this->perm + j);
			} while (j != i);

			lcm_continuous = lcm(lcm_continuous, sz);
		}
	}

	long long int remainder = n % lcm_continuous;
	int arrnew[this->len];

	for (int i = 0; i < this->len; ++i)
		arrnew[i] = i;

	permutation p3(this->len, arrnew);
	for (lli i = 0; i < remainder; ++i)
		p3 = p3 * (*this);

	return p3;
}

bool permutation::is_power(permutation const &q) const
{
	bool visited[103];
	for (int i = 0; i < 103; ++i)
		visited[i] = false;

	lli lcm_continuous = 1;
	for (int i = 0; i < this->len; ++i)
	{
		if (!visited[i])
		{
			lli sz = 0, j = i;
			do {
				visited[j] = 1;
				++sz;
				j = *(this->perm + j);
			} while (j != i);

			lcm_continuous = lcm(lcm_continuous, sz);
		}
	}

	int arrnew[this->len];
	for (int i = 0; i < this->len; ++i)
		arrnew[i] = i;

	permutation p3(this->len, arrnew);
	for (lli i = 0; i < lcm_continuous; ++i)
	{
		int counter = 0;
		int* arrtemp = p3.to_array();
		for (int j = 0; j < this->len; ++j)
			if (*(arrtemp + j) != *(this->perm + j))
				break;
			else
				counter++;
		if (counter == this->len)
			return true;
		p3 = p3 * q;
	}
	return false;
}

int permutation::log(permutation const &q) const
{
	bool visited[103];
	for (int i = 0; i < 103; ++i)
		visited[i] = false;

	lli lcm_continuous = 1;
	for (int i = 0; i < this->len; ++i)
	{
		if (!visited[i])
		{
			int sz = 0, j = i;
			do {
				visited[j] = 1;
				++sz;
				j = *(this->perm + j);
			} while (j != i);

			lcm_continuous = lcm(lcm_continuous, sz);
		}
	}

	int arrnew[this->len];
	for (int i = 0; i < this->len; ++i)
		arrnew[i] = i;

	permutation p3(this->len, arrnew);
	bool flag = false;
	for (lli i = 0; i < lcm_continuous; ++i)
	{
		lli counter = 0;
		int* arrtemp = p3.to_array();
		for (int j = 0; j < this->len; ++j)
			if (*(arrtemp + j) != *(this->perm + j))
				break;
			else
				counter++;
		if (counter == this->len)
		{
			flag = true;
			return i;
		}
		p3 = p3 * q;
	}
	return 0;
}
