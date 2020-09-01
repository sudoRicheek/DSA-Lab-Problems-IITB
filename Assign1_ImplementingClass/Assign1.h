#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <vector>
#include <map>
#include <iostream>
#include <cstddef>
#include <cmath>


typedef long long int lli;
const int MOD = 1e9 + 7;
using namespace std;

class permutation
{
	int len;
	int* perm;
	int gcd(int a, int b) const;
	int lcm(int a, int b) const;
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
	permutation const operator^(long long int n) const;
	bool is_power(permutation const &q) const;
	int log(permutation const &q) const;
};


permutation::permutation() //checked
{
	len = 0;
	perm = NULL;
}

permutation::permutation(permutation const &obj) //checked
{
	this->perm = new int[103];
	this->len = obj.size();
	int* arr_obj = obj.to_array();
	for (int i = 0; i < obj.size(); ++i)
		*(this->perm + i) = *(arr_obj + i);
}

permutation::permutation(int n, int a[]) //checked
{
	this->perm = new int[103];
	this->len = n;
	for (int i = 0; i < n; ++i)
		*(this->perm + i) = a[i];
}

permutation::~permutation()
{
	delete[] perm;
}

permutation const permutation::operator=(permutation const &q) //checked
{
	if (this->len == q.size())
	{
		int* arrtemp = q.to_array();
		for (int i = 0; i < q.size(); ++i)
			*(this->perm + i) = *(arrtemp + i);

		delete[] arrtemp;
		return *this;
	}

	this->len = q.size();
	if (this->perm == NULL || this->len != q.size())
		this->perm = new int[this->len];

	int* arrtemp = q.to_array();
	for (int i = 0; i < q.size(); ++i)
		*(this->perm + i) = *(arrtemp + i);

	delete[] arrtemp;
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
	int* arr = q.to_array();
	for (int i = 0; i < q.size(); ++i)
		*(comp_arr + i) = *(this->perm + * (arr + i));

	permutation newptr(q.size(), comp_arr);

	delete[] comp_arr;
	delete[] arr;
	return newptr;
}

permutation const permutation::square_root() const // O(N) solution !
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

	delete[] p;
	delete[] q;
	delete[] cnt;
	delete[] arrtemp;

	return pnew;
}


int permutation::gcd(int a, int b) const {
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

int permutation::lcm(int a, int b) const {
	return (a * b) / gcd(a, b);
}

permutation const permutation::operator^(lli n) const //O(N) solution !
{
	bool visited[103];
	int tempcycle[103];

	int arrpower[this->len];

	for (int i = 0; i < 103; ++i)
		visited[i] = false;

	for (int i = 0; i < this->len; ++i)
	{
		if (!visited[i])
		{
			lli sz = 0, j = i;
			do {
				visited[j] = 1;
				tempcycle[sz] = *(this->perm + j);
				++sz;
				j = *(this->perm + j);
			} while (j != i);

			lli remainder = n % sz;
			for (int loopind = 0; loopind < sz; ++loopind)
				arrpower[tempcycle[loopind]] = tempcycle[(remainder + loopind) % sz];
		}
	}
	permutation ptrnew(this->len, arrpower);
	return ptrnew;
}

bool permutation::is_power(permutation const &q) const // 6s for 1e6 testcases n = 100
{
	int *q_arr = q.to_array();

	bool visited[103];
	int temptemp[100];
	vector<int> sizes(q.size() + 1, -1);

	for (int i = 0; i < 103; ++i)
		visited[i] = false;

	for (int i = 0; i < q.size(); ++i) // O(N)
	{
		if (!visited[i])
		{
			lli sz = 0, j = i;
			do {
				visited[j] = 1;
				temptemp[sz] = *(q_arr + j);
				++sz;
				j = *(q_arr + j);
			} while (j != i);

			for (int k = 0; k < sz; ++k)
				sizes[temptemp[k]] = sz;
		}
	}

	vector<int> szrem(q.size() + 1, -1); //size = len+1, default val = 101;
	for (int i = 0; i < this->len; ++i) // O(N) ~ O(N^2)
	{
		bool internalflag = false;
		int start_cycle = i;
		for (int j = 0; ; ++j)
		{
			if (start_cycle == *(this->perm + i))
			{
				if ((szrem[sizes[i]] != -1) && (szrem[sizes[i]] != j))
				{
					delete[] q_arr;
					return false;
				}
				szrem[sizes[i]] = j;
				internalflag = true;
				break;
			}

			start_cycle = *(q_arr + start_cycle);
			if (start_cycle == i)
				break;
		}
		if (!internalflag)
		{
			delete[] q_arr;
			return false;
		}
	}

	vector<int> validelems;
	for (int i = 0; i <= q.size(); ++i)
		if (szrem[i] != -1)
			validelems.push_back(i);

	for (int i = 0; i < validelems.size(); ++i)
	{
		int gcdd;
		for (int j = i + 1; j < validelems.size(); j++)
		{
			gcdd = gcd(validelems[i], validelems[j]);
			if (szrem[validelems[i]] % gcdd != szrem[validelems[j]] % gcdd)
			{
				delete[] q_arr;
				return false;
			}
		}
	}

	delete[] q_arr;
	return true;
}

int permutation::log(permutation const &q) const
{
	int *q_arr = q.to_array();

	bool visited[103];
	int temptemp[100];
	vector<int> sizes(q.size(), -1);

	for (int i = 0; i < 103; ++i)
		visited[i] = false;

	for (int i = 0; i < q.size(); ++i) // O(N)
	{
		if (!visited[i])
		{
			lli sz = 0, j = i;
			do {
				visited[j] = 1;
				temptemp[sz] = *(q_arr + j);
				++sz;
				j = *(q_arr + j);
			} while (j != i);

			for (int k = 0; k < sz; ++k)
				sizes[temptemp[k]] = sz;
		}
	}

	vector<int> szrem(q.size() + 1, -1); //size = len+1, default val = 101;
	for (int i = 0; i < this->len; ++i) // O(N) ~ O(N^2)
	{
		bool internalflag = false;
		int start_cycle = i;
		for (int j = 0; ; ++j)
		{
			if (start_cycle == *(this->perm + i))
			{
				if ((szrem[sizes[i]] != -1) && (szrem[sizes[i]] != j))
				{
					delete[] q_arr;
					return 0;
				}
				szrem[sizes[i]] = j;
				internalflag = true;
				break;
			}

			start_cycle = *(q_arr + start_cycle);
			if (start_cycle == i)
				break;
		}
		if (!internalflag)
		{
			delete[] q_arr;
			return 0;
		}
	}

	map<int, int> maxmultiple;
	for (int i = 2; i <= q.size(); ++i) // O(nlgn)
	{
		int rem = szrem[i];
		int counter = i;
		int maxii = 0;
		//cout << i << " " << rem << endl;
		if (rem != -1)
		{
			for (int j = 1; j < 100; ++j)
			{
				counter = j * i;
				if (counter > q.size())
					break;
				if ((szrem[counter] != -1) && (szrem[counter] % i != rem))
				{
					delete[] q_arr;
					return 0;
				}
				if (szrem[counter] != -1)
					maxii = max(maxii, counter);
			}
			maxmultiple[maxii] = szrem[maxii];
		}
	}

	if (maxmultiple.size() == 1)
	{
		delete[] q_arr;
		return maxmultiple.begin()->second;
	}

	map<int, int>::iterator itr;
	lli quo = 1, remainder = 0;
	//cout << "hamba : " << endl;
	for (itr = maxmultiple.begin(); itr != maxmultiple.end(); ++itr)
	{
		//cout << itr->first << " : " << itr->second << endl;
		lli oldquo = quo;
		lli temp = 0;
		quo = lcm(quo, itr->first);
		if (oldquo == quo)
			continue;

		for (lli i = 0; temp < quo; ++i)
		{
			temp = i * oldquo + remainder;
			if (temp % (itr->first) == itr->second)
			{
				remainder = temp;
				break;
			}
		}
	}

	permutation ptrnew = q ^ remainder;
	int* checker_arr = ptrnew.to_array();

	for (int i = 0; i < this->len; ++i)
		if (checker_arr[i] != *(this->perm + i))
		{
			delete[] q_arr;
			delete[] checker_arr;
			return 0;
		}

	delete[] q_arr;
	delete[] checker_arr;
	return remainder % MOD;
}
#endif
