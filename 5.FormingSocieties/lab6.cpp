#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long int lli;
const int N = 1300000;

int flats[N];
int great_left[N];
int great_right[N];

void part1(int n)
{
	great_left[0] = -1;
	for (int i = 1; i < n; ++i)
	{
		int j = i - 1;
		while ((j >= 0) && (flats[j] < flats[i]))
			j = great_left[j];
		great_left[i] = j;
	}

	great_right[n - 1] = n;
	for (int i = n - 2; i >= 0; --i)
	{
		int j = i + 1;
		while ((j < n) && (flats[j] < flats[i]))
			j = great_right[j];
		great_right[i] = j;
	}

	for (int i = 0; i < n; ++i)
	{
		lli controln = 1, left = 0, right = 0;

		right = great_right[i] - i;
		left = i - great_left[i];

		controln = left * right;
		cout << controln << " ";
	}
	cout << endl;
}

void part2(int n)
{
	lli count = 0;
	int l_less[n];
	l_less[0] = -1;
	for (int i = 1; i < n; ++i)
	{
		int j = i - 1;
		while ((j >= 0) && (flats[j] <= flats[i]))
			j = l_less[j];
		l_less[i] = j;
	}

	vector<int> can_reach;
	vector<int> index;
	int length = 1;
	can_reach.pb(flats[0]);
	index.pb(0);
	count++;
	for (int i = 1; i < n; ++i)
	{
		int insert_pt = lower_bound(can_reach.begin(), can_reach.end(), flats[i] + 0.5) - can_reach.begin();
		if (insert_pt == length)
		{
			can_reach.pb(flats[i]);
			index.pb(i);
			length++;
		}
		else
		{
			can_reach[insert_pt] = flats[i];
			index[insert_pt] = i;
			length = insert_pt + 1;
			can_reach.resize(length);
			index.resize(length);
		}
		int elem_after_lgt;
		if (l_less[i] == -1)
			elem_after_lgt = 0;
		else
			elem_after_lgt = lower_bound(index.begin(), index.end(), l_less[i]) - index.begin();
		count += length - elem_after_lgt;
	}
	cout << count << endl;
}

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> flats[i];
	part1(n);
	part2(n);
}


int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	solve();
	return 0;
}