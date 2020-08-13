#include <bits/stdc++.h>
using namespace std;

long long int josephus(long long int n, long long int k)
{
	if (n == 1)
		return 0;
	if (k == 1)
		return n - 1;
	if (k > n)
		return (josephus(n - 1, k) + k) % n;

	long long int result = josephus(n - n/k, k) - n%k;

	if (result < 0)
		result += n;
	else
		result += result / (k - 1);

	return result;
}

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	long long int n, k;
	cin >> n >> k;

	cout << josephus(n, k) % n + 1 << endl;

	return 0;
}