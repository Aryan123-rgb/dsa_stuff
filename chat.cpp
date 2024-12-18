#include <bits/stdc++.h>
using namespace std;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define nline "\n"
#define all(x) (x).begin(), (x).end()
#define ll long long

struct bag
{
    ll k, sum;
    multiset<ll> mt1, mt2;
    void init(ll _K)
    {
        k = _K;
        sum = 0;
        mt1.clear();
        mt2.clear();
    }
    void insert(ll x)
    {
        mt1.insert(x);
        sum += x;

        if (mt1.size() > k)
        {
            ll sm = *mt1.begin();
            sum -= sm;
            mt2.insert(sm);
            mt1.erase(mt1.find(sm));
        }
    }
    void remove(ll x)
    {
        if (mt1.find(x) != mt1.end())
        {
            mt1.erase(mt1.find(x));
            sum -= x;
        }
        else if (mt2.find(x) != mt2.end())
        {
            mt2.erase(mt2.find(x));
        }

        if (mt1.size() < k && !mt2.empty())
        {
            ll lg = *mt2.rbegin();
            mt1.insert(lg);
            sum += lg;
            mt2.erase(mt2.find(lg));
        }
    }
    ll get_sum()
    {
        return sum;
    }
};

void solve()
{
    ll k, q;
    cin >> k >> q;

    bag bg;
    bg.init(k);
    while (q--)
    {
        string s;
        cin >> s;
        if (s == "insert")
        {
            ll x;
            cin >> x;
            bg.insert(x);
        }
        else if (s == "remove")
        {
            ll x;
            cin >> x;
            bg.remove(x);
        }
        else
        {
            cout << bg.get_sum() << nline;
        }
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