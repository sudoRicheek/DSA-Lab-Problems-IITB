#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;

void chocolates()
{
	lli n, k;
	cin >> n >> k;

	vector<int> chocs(k, 0);

	for (int i = 0; i < k; ++i)
		cin >> chocs[i];

	//Let's increase the 0th bin
	int max_index;
	int max_increase;
	int inc;
	while (true)
	{
		max_increase = 0;
		max_index = 1;
		inc = 0;
		for (int i = k - 1; i > 0; i--)
		{
			if (chocs[i] == 0)
				continue;

			if (chocs[i] - k + i < 0)
				inc = 0;
			else
				inc = (chocs[i] - k + i) / k + 1; // increase of 0th val

			if (inc >= max_increase)
			{
				max_increase = inc;
				max_index = i;
			}
		}
		chocs[0] += max_increase;
		int chocs_index = chocs[max_index];
		chocs[max_index] = 0;

		for (int i = max_index + 1; i < k; ++i)
		{
			if (chocs_index - i + max_index < 0)
				break;
			chocs[i] += 1;
		}

		for (int i = 1; i < k; ++i)
		{
			if (chocs_index - k + max_index - i < 0)
				break;
			chocs[i] += (chocs_index - k + max_index - i) / k + 1;
		}

		cout << max_index << " ";

		if (chocs[0] == n)
			break;
	}
	cout << 0 << "\n";
}

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
/*
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
*/
	chocolates();

	return 0;
}