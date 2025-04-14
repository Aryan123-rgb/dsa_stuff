#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string L, R;
ll len;
ll dp[10010][2][2][2][2];

// Convert decimal string to binary string
string toBinary(string s)
{
    string res;
    ll numLen = s.size();
    vector<int> num;
    for (char c : s)
        num.push_back(c - '0');

    while (!num.empty())
    {
        int rem = 0;
        vector<int> newNum;
        for (int d : num)
        {
            int cur = rem * 10 + d;
            newNum.push_back(cur / 2);
            rem = cur % 2;
        }
        res += (char)(rem + '0');

        // Remove leading zeros
        while (!newNum.empty() && newNum[0] == 0)
            newNum.erase(newNum.begin());
        num = newNum;
    }

    reverse(res.begin(), res.end());
    if (res.empty())
        res = "0";
    return res;
}

ll rec(ll index, ll lfl1, ll rfl1, ll lfl2, ll rfl2)
{
    if (index == len)
        return 0;

    if (dp[index][lfl1][rfl1][lfl2][rfl2] != -1)
        return dp[index][lfl1][rfl1][lfl2][rfl2];

    ll lnum = L[index] - '0', rnum = R[index] - '0';

    ll s1 = (lfl1 == 1 ? lnum : 0);
    ll e1 = (rfl1 == 1 ? rnum : 1);
    ll s2 = (lfl2 == 1 ? lnum : 0);
    ll e2 = (rfl2 == 1 ? rnum : 1);

    ll ans = 0;
    for (ll i = s1; i <= e1; i++)
    {
        for (ll j = s2; j <= e2; j++)
        {
            ll nlfl1 = (lfl1 == 1 && i == lnum ? 1 : 0);
            ll nrfl1 = (rfl1 == 1 && i == rnum ? 1 : 0);
            ll nlfl2 = (lfl2 == 1 && j == lnum ? 1 : 0);
            ll nrfl2 = (rfl2 == 1 && j == rnum ? 1 : 0);

            ll xor_val = i ^ j;
            ll res = 0;
            ll bit_pos = len - 1 - index;
            if (xor_val == 1)
            {
                res = (1LL << bit_pos);
            }
            ans = max(ans, res + rec(index + 1, nlfl1, nrfl1, nlfl2, nrfl2));
        }
    }

    return dp[index][lfl1][rfl1][lfl2][rfl2] = ans;
}

void solve()
{
    string a, b;
    cin >> a >> b;
    L = toBinary(a);
    R = toBinary(b);
    while (L.length() < R.length())
        L.insert(L.begin(), '0');
    len = R.length();

    memset(dp, -1, sizeof(dp));
    cout << rec(0, 1, 1, 1, 1) << '\n';
}

signed main()
{
    ll t;
    cin >> t;
    while (t--)
        solve();
}