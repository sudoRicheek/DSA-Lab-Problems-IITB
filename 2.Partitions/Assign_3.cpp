#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;
lli dp[25][25]; //index is max and length

void rgseq(int n, lli rank)
{
	int maxi = 0;
	cout << 0 << " ";
	for (int i = 1; i < n - 1; ++i)
	{
		if (rank == 0)
		{
			cout << 0 << " ";
			continue;
		}

		int level = rank / (dp[maxi][i + 1]);

		if (level > maxi + 1)
			level = maxi + 1;

		cout << level << " ";

		rank -= level * dp[maxi][i + 1];
		maxi = max(maxi, level);
	}
	cout << rank << " " << endl;
}

lli ranking(int len, lli seq[])
{
	lli rank = 0, maxi = 0;
	for (int i = 1; i < len - 1; ++i)
	{
		rank += dp[maxi][i + 1] * (seq[i]);
		maxi = max(maxi, seq[i]);
	}
	rank += seq[len - 1];
	return rank;
}

void solve()
{
	int n, t;
	cin >> n >> t;
	for (int i = 0; i < n - 1; ++i)
		dp[i][n - 1] = i + 2;

	for (int l = n - 2; l > 0; --l)
		for (int m = 0; m <= n - 1; ++m)
			dp[m][l] += (dp[m][l + 1]) * (m + 1) + dp[m + 1][l + 1];

	lli seq[n];
	while (t--)
	{
		char ch;
		cin >> ch;
		if (ch == 'R')
		{
			for (int i = 0; i < n; ++i)
				cin >> seq[i];
			cout << ranking(n, seq) << endl;
		}
		else if (ch == 'U')
		{
			lli rank;
			cin >> rank;
			rgseq(n, rank);
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