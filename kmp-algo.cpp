#include <bits/stdc++.h>
using namespace std;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define nline "\n"
#define all(x) (x).begin(), (x).end()
#define ll long long

/*
given a string s, find min characters to add at the back to make the string palindrome
*/

void solve()
{
    string s;
    cin >> s;

    string rev = s;
    reverse(rev.begin(), rev.end());
    s = s + '#' + rev;

    ll n = s.length();
    ll kmp[n + 1];
    ll i = 0, j = -1;
    kmp[0] = -1;

    while (i < n)
    {
        while (j != -1 && s[i] != s[j])
        {
            j = kmp[j];
        }
        j++;
        i++;
        kmp[i] = j;
    }
    cout << s << endl;
    for (int i = 0; i <= n; i++)
    {
        cout << kmp[i] << " ";
    }
}

int main()
{
    fastio();
    ll t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}
