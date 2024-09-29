#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::cin;
using std::cout;

struct suffix
{
    int idx;
    std::pair<int, int> eq;
    int idx_old;
    int idx_v_mas;
};

struct point
{
    char ch;
    int idx;
};

bool cmp(const suffix& a, const suffix& b)
{
    return a.idx < b.idx;
}

void countingSort(std::vector<suffix>& arr)
{
    int n = arr.size();

    int max_val = arr[0].eq.first;
    int min_val = arr[0].eq.first;
    for (int i = 1; i < n; i++)
    {
        if (arr[i].eq.first > max_val) max_val = arr[i].eq.first;
        if (arr[i].eq.first < min_val) min_val = arr[i].eq.first;
    }

    int range = max_val - min_val + 1;

    std::vector<int> count(range, 0);
    std::vector<suffix> output(n);

    for (int i = 0; i < n; i++)
    {
        count[arr[i].eq.first - min_val]++;
    }

    for (int i = 1; i < range; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i].eq.first - min_val] - 1] = arr[i];
        count[arr[i].eq.first - min_val]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

bool cmp1(const point& a, const point& b)
{
    return a.ch < b.ch;
}

std::vector<int> getSortedIndices(const std::string& s)
{
    int n = int(s.size());

    std::vector<point> charIndices(n);

    for (int i = 0; i < n; i++)
    {
        charIndices[i] = { s[i], i };
    }

    std::sort(charIndices.begin(), charIndices.end(), cmp1);

    std::vector<int> sortedIndices(n);
    for (int i = 0; i < n; i++)
    {
        sortedIndices[i] = charIndices[i].idx;
    }

    return sortedIndices;
}

std::vector<suffix> suff_mas(std::string& str)
{
    int n = int(str.size());
    std::vector<suffix> suff_m(n);

    std::vector<int> t = getSortedIndices(str);

    std::unordered_map<int, std::pair<int, int>> mapp;

    for (int i = 0; i < n; i++)
    {
        suff_m[i].idx = t[i];
        suff_m[i].idx_v_mas = i;
    }

    suff_m[0].eq.first = 0;
    suff_m[0].idx_old = n - 1;

    std::vector<int> temp_eq(n, 0);

    for (int i = 1; i < n; i++)
    {
        if (str[suff_m[i].idx] != str[suff_m[i - 1].idx])
        {
            suff_m[i].eq.first = suff_m[i - 1].eq.first + 1;
        }
        else
        {
            suff_m[i].eq.first = suff_m[i - 1].eq.first;
        }
        suff_m[i].idx_old = suff_m[i].idx;
        mapp[t[i]] = std::make_pair(suff_m[i].eq.first, 0);
    }
    for (int k = 1; k < 2 * n; k *= 2)
    {
        for (int i = 0; i < n; i++)
        {
            if (suff_m[i].idx - k < 0)
            {
                suff_m[i].idx = suff_m[i].idx - k + n;
            }
            else
            {
                suff_m[i].idx = suff_m[i].idx - k;
            }
            suff_m[i].eq.first = mapp[suff_m[i].idx].first;
        }
        countingSort(suff_m);
        for (int i = 0; i < n; i++)
        {
            mapp[suff_m[i].idx] = std::make_pair(suff_m[i].eq.first, suff_m[i].eq.second);
        }

        for (int i = 0; i < n; i++)
        {
            suff_m[i].eq.second = mapp[(suff_m[i].idx + k) % n].first;
        }

        temp_eq[0] = 0;

        for (int i = 1; i < n; i++)
        {
            if (suff_m[i].eq != suff_m[i - 1].eq)
            {
                temp_eq[i] = temp_eq[i - 1] + 1;
            }
            else
            {
                temp_eq[i] = temp_eq[i - 1];
            }
        }

        for (int i = 1; i < n; i++)
        {
            suff_m[i].eq = std::make_pair(temp_eq[i], 0);
            mapp[suff_m[i].idx] = std::make_pair(suff_m[i].eq.first, suff_m[i].eq.second);
        }

        if (suff_m[n - 1].eq.first == n - 1)
            break;
    }

    return suff_m;
}

std::vector<int> buildLCPArray(const std::string& str, const std::vector<suffix>& suff_mas)
{
    int n = str.size();
    std::vector<int> rank(n, 0);
    std::vector<int> lcp(n, 0);

    for (int i = 0; i < n; i++)
    {
        rank[suff_mas[i].idx] = i;
    }

    int h = 0;
    for (int i = 0; i < n; i++)
    {
        if (rank[i] > 0)
        {
            int j = suff_mas[rank[i] - 1].idx;
            while (i + h < n && j + h < n && str[i + h] == str[j + h])
            {
                h++;
            }
            lcp[rank[i]] = h;
            if (h > 0)
            {
                h--;
            }
        }
    }

    return lcp;
}

std::vector<int> searchPatternWithLCP(const std::string& text, const std::string& pattern, const std::vector<suffix>& suff_mas, const std::vector<int>& lcp)
{
    int left = 0, right = int(suff_mas.size()) - 1;
    int pat_len = pattern.size();
    std::vector<int> positions;
    int n = text.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        int suffix_idx = suff_mas[mid].idx;

        if (suffix_idx == n) {
            right = mid - 1;
            continue;
        }

        std::string suffix = text.substr(suffix_idx, pat_len);

        if (suffix == pattern)
        {
            positions.push_back(suffix_idx);
            int i = mid - 1;
            while (i >= left && suff_mas[i].idx != n && text.substr(suff_mas[i].idx, pat_len) == pattern)
            {
                positions.push_back(suff_mas[i].idx);
                i--;
            }
            i = mid + 1;
            while (i <= right && suff_mas[i].idx != n && text.substr(suff_mas[i].idx, pat_len) == pattern)
            {
                positions.push_back(suff_mas[i].idx);
                i++;
            }
            break;
        }
        else if (suffix < pattern)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    std::sort(positions.begin(), positions.end());
    return positions;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    std::string s;
    cin >> s;
    s += "$";

    std::vector<suffix> suff = suff_mas(s);

    for (int i = 0; i < s.size(); i++)
    {
        if (suff[i].idx == s.size() - 1)
            continue;
        //cout << suff[i].idx << " ";
    }
    //cout << "\n";

    std::vector<int> lcp = buildLCPArray(s, suff);

    int kol = 0;
    std::string pattern;
    while (cin >> pattern)
    {
        kol++;
        if (pattern == "")
            continue;
        std::vector<int> found_positions = searchPatternWithLCP(s, pattern, suff, lcp);

        if (!found_positions.empty())
        {
            cout << kol << ": ";
            for (int j = 0; j < int(found_positions.size()); j++)
            {
                cout << found_positions[j] + 1;
                if (j + 1 != int(found_positions.size()))
                    cout << ", ";
            }
            cout << "\n";
        }
        else
        {
            continue;
        }
    }

    return 0;
}
