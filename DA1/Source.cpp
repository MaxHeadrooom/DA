#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using std::cin;
using std::cout;

using ll = int;

void sort(std::vector<std::pair<ll, ll>>& A, ll& i)
{
    const int n = i;
    const int k = 10;

    std::vector<int> C(k, 0);
    std::vector<std::pair<ll, ll>> B(n);
    std::vector<int> mas{ 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 };
    ll step = 1;

    for (int i = 0; i < 7; i++)
    {
        C.assign(k, 0);

        for (int j = 0; j < n; j++)
        {
            ll d = (A[j].first / mas[i]) % 10;
            C[d]++;
        }


        for (int j = 1; j < k; j++)
        {
            C[j] += C[j - 1];
        }

        for (int j = n - 1; j >= 0; j--)
        {
            ll d = (A[j].first / mas[i]) % 10;
            B[C[d] - 1] = A[j];
            C[d]--;
        }

        std::swap(A, B);
    }
}

ll day, mon, year;

ll pars(const std::string& s)
{
    ll i = 0;
    ll kol = 0;
    std::vector<ll> mas(3, 0);

    while (i < s.size())
    {
        if (s[i] == '.')
            kol++;
        else
        {
            mas[kol] = mas[kol] * 10 + (s[i] - '0');
        }
        i++;
    }

    return (mas[0] + mas[1] * 30 + mas[2] * 365);
}

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    std::string key = "", str = "", keyy;

    std::vector<std::pair<ll, ll>> m(1e6);
    std::vector<std::string> data;
    int i = 0;

    std::ifstream f("input.txt");

    while (
        f >> key
        //keyy != "34re324"
        //std::getline(cin, keyy)
        )
    {
        //std::getline(cin, keyy);
        //if (keyy.empty())
           // continue;

        std::pair<ll, ll> x;

        f >> str;

        x.second = data.size();
        data.push_back(key + '\t' + str);
        std::string s = "", s1 = "";

        if (key.empty() or str.empty() or key == "" or str == " ")
            continue;

        //if (key == "3")
          //  break;

        x.first = pars(key);

        //ll prom = x.days.size();

       /* for (int i = 0; i < 7 - prom; i++)
        {
            x.days = "0" + x.days;
        }*/

        m[i] = x;
        i++;
    }

    sort(m, i);

    std::ofstream out;
    out.open("output.txt");
    for (int j = 0; j < data.size(); j++)
    {
        out << data[m[j].second] << '\n';
    }
    out.close();

    return 0;
}