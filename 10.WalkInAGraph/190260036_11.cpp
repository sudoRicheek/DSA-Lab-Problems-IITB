#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back
typedef long long int lli;

int n, m;
int u, v;
vector<vector<int>> adjlist(1000100, vector<int>());

void solve()
{
	cin >> n >> m >> u >> v;
	int x, y;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y;
		adjlist[2 * x + 1].pb(2 * y + 2);
		adjlist[2 * y + 2].pb(2 * x + 1);
		adjlist[2 * x + 2].pb(2 * y + 1);
		adjlist[2 * y + 1].pb(2 * x + 2);
	}

	int s1 = 2 * u + 1; // source vertex

	queue<int> q;
	vector<bool> used(2 * n + 5);
	vector<int> d(2 * n + 5), p(2 * n + 5);

	q.push(s1);
	used[s1] = true;
	p[s1] = -1;
	while (!q.empty()) {
		int v1 = q.front();
		q.pop();
		for (int u1 : adjlist[v1]) {
			if (!used[u1]) {
				used[u1] = true;
				q.push(u1);
				d[u1] = d[v1] + 1;
				p[u1] = v1;
			}
		}
	}

	int s2 = 2 * v + 1;

	//q is empty
	vector<bool> used2(2 * n + 5);
	vector<int> d2(2 * n + 5), p2(2 * n + 5);

	q.push(s2);
	used2[s2] = true;
	p2[s2] = -1;
	while (!q.empty()) {
		int v2 = q.front();
		q.pop();
		for (int u2 : adjlist[v2]) {
			if (!used2[u2]) {
				used2[u2] = true;
				q.push(u2);
				d2[u2] = d2[v2] + 1;
				p2[u2] = v2;
			}
		}
	}


	// for (int i : d)
	// {
	// 	cout << i << " ";
	// }
	// cout << endl;
	// for (int i : d2)
	// {
	// 	cout << i << " ";
	// }
	// cout << endl;
	int min = -1;
	vector<int> answer;
	for (int i = 0, j = 0; i < 2 * n; i = j * 2)
	{
		if (d[i + 1] == d2[i + 1])
		{
			if (min == -1 && d[i + 1] > 0)
			{
				min = d[i + 1];
				answer.pb(j);
			}
			else if (min > 0 && d[i + 1] == min)
			{
				answer.pb(j);
			}
			else if (min > 0 && d[i + 1] < min && d[i + 1] > 0)
			{
				min = d[i + 1];
				answer.clear();
				answer.pb(j);
			}
		}
		if (d[i + 2] == d2[i + 2])
		{
			if (min == -1 && d[i + 2] > 0)
			{
				min = d[i + 2];
				answer.pb(j);
			}
			else if (min > 0 && d[i + 2] == min)
			{
				answer.pb(j);
			}
			else if (min > 0 && d[i + 2] < min && d[i + 2] > 0)
			{
				min = d[i + 2];
				answer.clear();
				answer.pb(j);
			}
		}
		j++;
	}
	if (min == -1)
	{
		cout << "impossible" << endl;
	}
	else
	{
		cout << "possible" << endl;;
		cout << min << endl;
		for (int i : answer)
		{
			cout << i << " ";
		}
		cout << endl;
	}
}


int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	solve();

	return 0;
}