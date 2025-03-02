#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using ll = long long;
#define nline "\n"
using namespace std;

/*
Problem Summary:
----------------
Given an array of N integers, find a subarray that meets the following conditions:
1. Contains at most K odd numbers.
2. Has the maximum possible sum that does not exceed D.

Input:
- T: Number of test cases (1 ≤ T ≤ 10).
- For each test case:
  - N, K, D: Length of the array, maximum allowed odd numbers, and maximum allowed sum (-1e9 ≤ D ≤ 1e9).
  - N space-separated integers (-1e4 ≤ Ai ≤ 1e4).

Output:
- The maximum possible sum of a valid subarray.
- Print "IMPOSSIBLE" if no valid subarray exists.

Constraints:
- 1 ≤ N ≤ 10^5
- 0 ≤ K ≤ 10^5

Example:
---------
Input:
6
3 2 5
1 2 3
3 1 2
-3 -1 -3
5 2 8
-1 2 3 4 -5
7 0 -2
1 -4 1 0 1 0 2
10 3 14
1 0 -7 1 -10 4 -2 10 -1 3
3 0 1000
-101 201 -301

Output:
5
-1
8
-4
14
IMPOSSIBLE

*/

void solve()
{
    ll n, k, d;
    cin >> n >> k >> d;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<ll> pre(n, 0);
    for (ll i = 0; i < n; i++)
    {
        pre[i] += v[i];
        if (i)
            pre[i] += pre[i - 1];
    }
    multiset<ll> mt;
    ll r = 0, odd = 0;
    ll ans = -1e18;
    // debug(pre);
    for (ll l = 0; l < n; l++)
    {
        if (l >= r)
        {
            odd = 0;
            mt.clear();
        }
        r = max(r, l);
        while (r < n)
        {
            mt.insert(pre[r]);
            if (abs(v[r]) % 2 == 1)
            {
                odd += 1;
            }
            if (odd > k)
            {
                odd -= 1;
                mt.erase(mt.find(pre[r]));
                break;
            }
            r += 1;
        }
        ll x = (l - 1 >= 0 ? pre[l - 1] : 0);
        auto it = mt.upper_bound(x + d);
        // debug(l);
        // debug(r);
        // debug(odd);
        if (it != mt.begin())
        {
            it--;
            ans = max(ans, *it - x);
            ll res = *it - x;
            // debug(*it);
        }
        if (v[l] % 2 == 1 || v[l] % 2 == -1)
        {
            odd -= 1;
        }
        if (mt.find(pre[l]) != mt.end())
        {
            mt.erase(mt.find(pre[l]));
        }
    }
    if (ans == -1e18)
    {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << ans << nline;
}

signed main()
{
    int t = 1;
    cin >> t;
    for (ll i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}