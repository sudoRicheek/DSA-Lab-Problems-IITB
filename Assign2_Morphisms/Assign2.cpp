#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define pb push_back
typedef long long int lli;
typedef unsigned long long int ulli;

const lli INF = 1e18 + 5;
int k;
vector<string> f;
int vectorize[6][6];
vector<lli> counts[6];
lli smallestdepth;

lli lengthf(lli n) //216logn
{
	ulli poww[6][6];
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			if (i == j)
				poww[i][j] = 1;
			else
				poww[i][j] = 0;

	ulli tempvect[6][6];
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			tempvect[i][j] = vectorize[i][j];

	ulli b = n;
	while (b > 0)
	{
		if (b & 1)
		{
			ulli anothervect[6][6];
			for (int i = 0; i < k; ++i)
				for (int j = 0; j < k; ++j)
					anothervect[i][j] = poww[i][j];

			for (int i = 0; i < k; ++i)
			{
				for (int j = 0; j < k; ++j)
				{
					poww[i][j] = 0;
					for (int idx = 0; idx < k; ++idx)
						poww[i][j] += anothervect[i][idx] * tempvect[idx][j];
				}
			}
		}

		ulli anothervect[6][6];
		for (int i = 0; i < k; ++i)
			for (int j = 0; j < k; ++j)
				anothervect[i][j] = tempvect[i][j];

		for (int i = 0; i < k; ++i)
		{
			for (int j = 0; j < k; ++j)
			{
				tempvect[i][j] = 0;
				for (int idx = 0; idx < k; ++idx)
					tempvect[i][j] += anothervect[i][idx] * anothervect[idx][j];
			}
		}
		b >>= 1;
	}
	ulli res = 0;
	for (int i = 0; i < k; ++i)
		res += poww[0][i];

	return res;
}

void lengthsieve(lli charpos)
{
	for (int i = 0; i < 6; ++i)
		counts[i].clear();

	bool flag = true;
	ulli res = 0;
	ulli poww[6][6];
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			if (i == j)
				poww[i][j] = 1;
			else
				poww[i][j] = 0;

	ulli anothervect[6][6];
	while (true)
	{
		for (int i = 0; i < k; ++i)
			for (int j = 0; j < k; ++j)
				anothervect[i][j] = poww[i][j];

		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < k; ++j) {
				poww[i][j] = 0;
				for (int idx = 0; idx < k; ++idx)
					poww[i][j] += anothervect[i][idx] * vectorize[idx][j];
			}
		}

		for (int i = 0; i < k; ++i) {
			res = 0;
			for (int j = 0; j < k; ++j)
				res += poww[i][j];
			if ((i == 0) && (res > charpos)) {
				flag = false;
				break;
			}
			counts[i].pb(res);
		}
		if (!flag)
			break;
	}
	// for (int i = 0; i < k; ++i) {
	// 	for (int j = 0; j < counts[i].size(); ++j)
	// 		cout << counts[i][j] << " ";
	// 	cout << endl;
	// }
}

int charnexpo(lli charpos, lli pow, lli parent_char, lli which_char)
{
	if (pow == -1)
		return f[parent_char][charpos];
	if (charpos >= counts[f[parent_char][which_char] - 97][pow])
		return charnexpo(charpos - counts[f[parent_char][which_char] - 97][pow],
		                 pow, parent_char, which_char + 1);
	else
		return charnexpo(charpos, pow - 1,
		                 (f[parent_char][which_char] - 97), 0);
}

void charn(lli charpos)
{
	cout << (char)charnexpo(charpos, counts[0].size() - 1, 0, 0) << "\n";
}

lli fiboinv(string& word, lli depth, lli index)
{
	if (word == "")
		return -1;

	if ((word.size() == 1) && (word[0] == 'a'))
	{
		smallestdepth = min(smallestdepth, depth);
		return index;
	}

	if (depth >= smallestdepth)
		return -1;

	string inv = "";
	string inv2 = "";
	int i = 0;

	if (word[0] == 'b')
	{
		index += lengthf(depth);
		inv += "a";
		i++;
	}

	for (; i < word.size() - 1; i++)
	{
		if ((word[i] == 'a') && (word[i + 1] == 'b')) {
			inv += "a";
			i++;
		}
		else if ((word[i] == 'a') && (word[i + 1] == 'a'))
		{
			if (inv != "")
				if (inv[inv.size() - 1] != 'b')
					inv += "b";
				else
					return -1;
			else
				inv += "b";
		}
		else
			return -1;
	}

	if (i == word.size() - 1)
		if (word[i] == 'a')
		{
			if (inv[inv.size() - 1] != 'b')
				inv2 = inv + "b";
			inv = inv + "a";
		}
		else
			return -1;

	if (inv == "aaa" || inv == "aa")
		inv = "";

	lli res = fiboinv(inv, depth + 1, index);
	lli res2 = fiboinv(inv2, depth + 1, index);

	if ((res != -1) && (res2 != -1))
		return min(res, res2);
	else if ((res != -1) && (res2 == -1))
		return res;
	else if ((res == -1) && (res2 != -1))
		return res2;
	else
		return -1;
}

void subsidxfibo(string& word)
{
	smallestdepth = 1000000000;
	bool flag = true;
	for (int i = 0; i < word.length(); ++i)
		if ((word[i] != 'a') && (word[i] != 'b'))
			flag = false;

	if (flag)
	{
		lli smoldx = fiboinv(word, 0, 0);
		if (smoldx == -1)
			cout << -1 << endl;
		else
			cout << smallestdepth << " " << smoldx << endl;
	}
	else
		cout << -1 << endl;

}

lli thueinv(string& word, lli depth, lli index)
{
	string inv = "";
	string inv2 = "";

	if (word == "")
		return -1;

	if ((word.length() == 1) && word[0] == 'a')
	{
		smallestdepth = min(smallestdepth, depth);
		return index;
	}

	if (depth >= smallestdepth)
		return -1;

	//0th index case
	int i = 0;
	for (; i < word.length() - 1; i += 2)
	{
		if ((word[i] == 'a') && (word[i + 1] == 'b')) {
			if (inv.size() >= 2)
				if ((inv[inv.size() - 1] == 'a') && (inv[inv.size() - 2] == 'a')) {
					inv = "";
					break;
				}
				else
					inv += "a";
			else
				inv += "a";
		}
		else if ((word[i] == 'b') && (word[i + 1] == 'a')) {
			if (inv.size() >= 2)
				if ((inv[inv.size() - 1] == 'b') && (inv[inv.size() - 2] == 'b')) {
					inv = "";
					break;
				}
				else
					inv += "b";
			else
				inv += "b";
		}
		else {
			inv = "";
			break;
		}
	}
	if (inv != "")
		if (i == word.length() - 1)
			if (inv.size() >= 2)
				if ((inv[inv.size() - 1] == word[i]) && (inv[inv.size() - 2] == word[i]))
					inv = "";
				else
					inv += word[i];
			else
				inv += word[i];

	// -1th index case
	int j = 1;
	if (word[0] == 'b')
		inv2 += "a";
	else
		inv2 += "b";

	for (; j < word.length() - 1; j += 2)
	{
		if ((word[j] == 'a') && (word[j + 1] == 'b')) {
			if (inv2.size() >= 2)
				if ((inv2[inv2.size() - 1] == 'a') && (inv2[inv2.size() - 2] == 'a')) {
					inv2 = "";
					break;
				}
				else
					inv2 += "a";
			else
				inv2 += "a";
		}
		else if ((word[j] == 'b') && (word[j + 1] == 'a')) {
			if (inv2.size() >= 2)
				if ((inv2[inv2.size() - 1] == 'b') && (inv2[inv2.size() - 2] == 'b')) {
					inv2 = "";
					break;
				}
				else
					inv2 += "b";
			else
				inv2 += "b";
		}
		else {
			inv2 = "";
			break;
		}
	}

	if (inv2 != "")
		if (j == word.length() - 1)
			if (inv2.size() >= 2)
				if ((inv2[inv2.size() - 1] == word[j]) && (inv2[inv2.size() - 2] == word[j]))
					inv2 = "";
				else
					inv2 += word[j];
			else
				inv2 += word[j];

	lli res = thueinv(inv, depth + 1, index);
	lli res2 = thueinv(inv2, depth + 1, index + lengthf(depth));

	if ((res != -1) && (res2 != -1))
		return min(res, res2);
	else if ((res != -1) && (res2 == -1))
		return res;
	else if ((res == -1) && (res2 != -1))
		return res2;
	else
		return -1;
}

void subsidxthue(string& word)
{
	bool flag = true;
	for (int i = 0; i < word.length(); ++i)
		if ((word[i] != 'a') && (word[i] != 'b'))
			flag = false;

	if (flag)
	{
		smallestdepth = 1000000000;
		lli smoldx = thueinv(word, 0, 0);
		if (smoldx == -1)
			cout << -1 << endl;
		else
			cout << smallestdepth << " " << smoldx << endl;
	}
	else
		cout << -1 << endl;

}


void subseqidxfibo(string& word)
{

}

void solve()
{
	cin >> k;
	string buff;
	getline(cin, buff);

	bool exponentialcase = true;
	bool lengthsieved = false;
	for (int i = 0; i < k; ++i)
	{
		string inp;
		getline(cin, inp);
		f.pb(inp);

		if (inp.length() < 2)
			exponentialcase = false;
	}

	for (int i = 0; i < k; ++i)
		for (int j = 0; j < f[i].length(); ++j)
			vectorize[i][f[i][j] - 97]++;

	int t;
	cin >> t;
	while (t--)
	{
		int op;
		cin >> op;
		if (op == 0)
		{
			lli n;
			cin >> n;
			cout << lengthf(n) << endl; // length of f^n
		}
		else if (op == 1)
		{
			lli idx;
			cin >> idx;
			if ((exponentialcase == true) || ((k >= 2) && (f[0] == "ab") && (f[1] == "a"))) {
				if (!lengthsieved)
				{
					lengthsieve(INF);
					lengthsieved = true;
				}
				charn(idx); // character at nth index
			}
			else
				cout << 'a' << endl;
		}
		else if (op == 2)
		{
			string str;
			cin >> str;
			if ((k == 2) && (f[0] == "ab") && (f[1] == "a"))
				subsidxfibo(str);
			else if ((k == 2) && (f[0] == "ab") && (f[1] == "ba"))
				subsidxthue(str);
			else
				cout << -1 << endl;
		}
		else if (op == 3)
		{
			string str;
			cin >> str;
			if ((k == 2) && (f[0] == "ab") && (f[1] == "a"))
				subseqidxfibo(str);
			// else if ((k == 2) && (f[0] == "ab") && (f[1] == "ba"))
			// 	subseqidxthue(str);
			else
				cout << -1 << endl;
			// smallest n such that its a subsequence
		}
	}
}

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	solve();
	return 0;
}