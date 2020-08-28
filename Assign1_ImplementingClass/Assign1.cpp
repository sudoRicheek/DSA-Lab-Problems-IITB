#include "Assign1.h"

permutation::permutation() //checked
{
	len = 0;
	perm = NULL;
}

permutation::permutation(permutation const &obj) //checked
{
	this->perm = new int[obj.size()];
	this->len = obj.len;
	for (int i = 0; i < obj.len; ++i)
		*(this->perm + i) = *(obj.perm + i);
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
		inv[i] = 0;

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
	permutation pow2 = (*this) * (*this);
	bool  flag = true;
	for (int i = 0; i < this->len; ++i)
	{
		if (*(pow2.to_array() + i) != *(this->perm + i))
		{
			flag = false;
			break;
		}
	}
	if (!flag)
	{
		int arr[this->len];
		for (int i = 0; i < this->len; ++i)
			arr[i] = i;
		pow2 = permutation(this->len, arr);
	}
	return pow2;
}