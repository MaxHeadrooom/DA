#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ll m, n;

    cin >> m >> n;

    vector<vector<double>> mas(m, vector<double>(n + 2, 0));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cin >> mas[i][j];
        }
        mas[i][n + 1] = i + 1;
    }

    vector<ll> mi;

    for (int i = 0; i < n; i++)
    {
        ll price = 1e9;
        ll pos = -1;

        for (int j = i; j < m; j++)
        {
            if (mas[j][i] != 0 and mas[j][n] < price)
            {
                price = mas[j][n];
                pos = j;
            }
        }

        if (pos == -1)
        {
            cout << -1 << '\n';
            exit(0);
        }

        swap(mas[i], mas[pos]);

        mi.push_back(mas[i][n + 1]);

        for (int j = i + 1; j < m; j++)
        {
            double pivot = mas[j][i] / mas[i][i];
            for (int k = i; k < n; k++)
            {
                mas[j][k] -= mas[i][k] * pivot;
            }
        }
    }

    sort(mi.begin(), mi.end());

    for (int i = 0; i < int(mi.size()); i++)
    {
        cout << mi[i] << " ";
    }

    return 0;
}
