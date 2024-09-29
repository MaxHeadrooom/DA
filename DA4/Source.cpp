#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using ll = long long;

std::vector<ll> z_func(const std::vector<std::string>& s)
{
    ll n = static_cast<ll>(s.size());
    std::vector<ll> z(n, 0);
    ll l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i <= r)
            z[i] = std::min(z[i - l], r - i + 1);
        while (i + z[i] < n and (s[n - z[i] - 1] == s[n - 1 - (i + z[i])]))
        {
            z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

void BadCharacter(const std::vector<std::string>& pattern, std::map<std::string, ll>& badchar)
{
    for (int i = 0; i < static_cast<ll>(pattern.size()); i++)
    {
        badchar[pattern[i]] = i;
    }
}

std::vector<ll> goodSuffix(const std::vector<std::string>& pats)
{
    std::vector<ll> Nj = z_func(pats);
    std::reverse(Nj.begin(), Nj.end());

    std::vector<ll> Li(static_cast<ll>(pats.size()) + 1, static_cast<ll>(pats.size()));

    int j = 0;
    for (int i = 0; i < static_cast<ll>(pats.size()) - 1; i++)
    {
        j = static_cast<ll>(pats.size()) - Nj[i];
        Li[j] = i;
    }

    std::vector<ll> l(static_cast<ll>(pats.size()) + 1, static_cast<ll>(pats.size()));
    for (int i = static_cast<ll>(pats.size()) - 1; i >= 0; i--)
    {
        j = static_cast<ll>(pats.size()) - i;
        if (Nj[j - 1] == j)
        {
            l[i] = (j - 1);
        }
        else
        {
            l[i] = l[i + 1];
        }
    }

    for (int i = 0; i < static_cast<ll>(pats.size()) + 1; i++)
    {
        if (Li[i] == static_cast<ll>(pats.size()))
        {
            Li[i] = l[i];
        }
    }

    for (int i = 0; i < static_cast<ll>(Li.size()); i++)
    {
        if (Li[i] != static_cast<ll>(pats.size()))
        {
            Li[i] = static_cast<ll>(pats.size()) - Li[i] - 1;
        }
    }

    return Li;
}

void Input(std::vector<std::string>& pattern, std::vector<std::string>& text, std::vector<std::pair<ll, ll>>& positions)
{
    std::string word = "";
    char c;
    c = getchar();
    bool flag = false;
    ll linePos = 1;
    ll columnPos = 0;
    std::pair<ll, ll> pos;

    while (c != '\n')
    {
        if (c == ' ' and flag)
        {
            flag = false;
            pattern.push_back(word);
            word = "";
        }
        else
        {
            if (c != ' ')
            {
                flag = true;
                word += std::tolower(c);
            }
        }
        c = getchar();
    }

    if (flag)
    {
        pattern.push_back(word);
    }

    word = "";
    flag = false;

    while ((c = getchar()) != EOF and c != '#')
    {
        if (c == ' ' and flag)
        {
            flag = false;
            columnPos++;
            text.push_back(word);
            pos.first = linePos;
            pos.second = columnPos;
            positions.push_back(pos);
            word = "";
        }
        else
        {
            if (c == '\n')
            {
                if (flag)
                {
                    columnPos++;
                    text.push_back(word);
                    pos.first = linePos;
                    pos.second = columnPos;
                    positions.push_back(pos);
                    word = "";
                }
                flag = false;
                columnPos = 0;
                linePos++;
            }
            else
            {
                if (c != ' ')
                {
                    flag = true;
                    word += std::tolower(c);
                }
            }
        }
    }

    if (flag)
    {
        columnPos++;
        text.push_back(word);
        pos.first = linePos;
        pos.second = columnPos;
        positions.push_back(pos);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<std::string> pat;
    std::vector<std::string> text;
    std::vector<std::pair<ll, ll>> positions;
    Input(pat, text, positions);

    if (pat.size() > text.size())
    {
        exit(0);
    }


    std::map<std::string, ll> badchar;
    BadCharacter(pat, badchar);

    std::vector<ll> goodsuff(static_cast<ll>(pat.size()), 0);
    goodsuff = goodSuffix(pat);

    ll patternPos, bound = 0, shift = 0, textPos = 0;

    while (textPos < static_cast<ll>(text.size()) - static_cast<ll>(pat.size()) + 1)
    {
        for (patternPos = static_cast<ll>(pat.size()) - 1; patternPos >= bound; patternPos--)
        {
            if (pat[patternPos] != text[textPos + patternPos])
            {
                break;
            }
        }

        if (patternPos < bound)
        {
            std::cout << positions[textPos].first << ", " << positions[textPos].second << '\n';
            bound = static_cast<ll>(pat.size()) - goodsuff[0];
            patternPos = -1;
        }
        else
        {
            bound = 0;
        }

        if (patternPos < bound)
        {
            shift = goodsuff[patternPos + 1];
        }
        else
        {
            shift = std::max({ goodsuff[patternPos + 1], patternPos - badchar[text[textPos + patternPos]], 1ll });
        }

        textPos += shift;
    }

    return 0;
}
