#include <bits/stdc++.h>

using namespace std;

using graph = vector<vector<int>>;

bool dfs(const graph& g, int u, vector<int>& matching, vector<bool>& visited)
{
	if (visited[u])
		return false;
	visited[u] = true;
	for (int v : g[u])
	{
		if (matching[v] == -1 or dfs(g, matching[v], matching, visited))
		{
			matching[v] = u;
			return true;
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	long long b, pos, n, k, m;
	set<int> st;
	queue<int> q;

	long long start, finish, t;

	cin >> n >> m;
	graph g(n);

	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = 0; i < n; i++)
	{
		sort(g[i].begin(), g[i].end());
	}

	int ans = 0;

	vector<int> matching(n, -1);
	for (int i = 0; i < n; i++)
	{
		vector<bool> visited(n, false);
		dfs(g, i, matching, visited);
	}

	vector<pair<int, int>> otv;

	for (int v = 0; v < n; v++)
	{
		if (matching[v] != -1)
		{
			int u = matching[v];
			if (u < v)
			{
				otv.push_back(make_pair(u, v));
			}
		}
	}

	cout << int(otv.size()) << '\n';

	sort(otv.begin(), otv.end());

	for (int i = 0; i < int(otv.size()); i++)
	{
		cout << otv[i].first + 1 << " " << otv[i].second + 1 << '\n';
	}
	return 0;
};