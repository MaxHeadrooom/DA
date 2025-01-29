#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
	ll n, m;

	cin >> n >> m;

	vector<vector<ll>> dp(n + 2, vector<ll>(m + 2, 1e18));
	vector<vector<ll>> dp1(n + 2, vector<ll>(m + 2, 1e18));

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cin >> dp[i][j];
			dp1[i][j] = dp[i][j];
		}
	}

	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			dp1[i][j] = min(dp1[i - 1][j + 1], min(dp1[i - 1][j], dp1[i - 1][j - 1])) + dp[i][j];
		}
	}

	//cout << "========================\n";

	/*for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			cout << dp1[i][j] << " ";
		}
		cout << '\n';
	}*/


	ll mi = 1e18, pos = -1;

	for (int i = 1; i <= m; i++)
	{
		if (dp1[n][i] < mi)
		{
			mi = dp1[n][i];
			pos = i;
		}
	}

	cout << mi << '\n';

	ll res = dp1[n][pos];

	vector<pair<int, int>> path;

	path.push_back(make_pair(n, pos));

	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = m; j >= 1; j--)
		{
			if (abs(path[path.size() - 1].second - j) <= 1)
			{
				if (dp1[i][j] + dp[path[path.size() - 1].first][path[path.size() - 1].second] == res)
				{
					res -= dp[path[path.size() - 1].first][path[path.size() - 1].second];
					path.push_back(make_pair(i, j));
				}
			}
		}
	}

	for (int i = path.size() - 1; i >= 0; i--)
	{
		cout << "(" << path[i].first << "," << path[i].second << ") ";
	}

}
