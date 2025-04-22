#include <bits/stdc++.h>
using namespace std;
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define MOD 1000000007

typedef long long ll;

ll binExp(ll a, ll b, ll m)
{
    ll ans = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}

struct sliding_mode
{
    map<ll, ll> mp;
    set<pair<ll, ll>> st; // {freq, -1 * ele}
    void init()
    {
        mp.clear();
        st.clear();
    }
    void insert(ll x)
    {
        x = -x;
        if (mp.find(x) != mp.end())
        {
            if (st.find({mp[x], x}) != st.end())
            {
                st.erase({mp[x], x});
            }
            mp[x]++;
            st.insert({mp[x], x});
        }
        else
        {
            mp[x]++;
            st.insert({mp[x], x});
        }
    }

    void remove(ll x)
    {
        x = -x;
        if (st.find({mp[x], x}) != st.end())
        {
            st.erase({mp[x], x});
        }
        mp[x]--;
        if (mp[x] > 0)
        {
            st.insert({mp[x], x});
        }
    }
    ll get_mode()
    {
        if (st.empty())
        {
            return -1;
        }
        ll ele = st.rbegin()->second;
        return -1 * ele;
    }
};

struct sliding_median
{
    multiset<ll> lo, hi;
    void init()
    {
        lo.clear();
        hi.clear();
    }

    void insert(ll x)
    {
        hi.insert(x);
        rebalance();
    }

    void remove(ll x)
    {
        if (hi.find(x) != hi.end())
        {
            hi.erase(hi.find(x));
            rebalance();
            return;
        }
        if (lo.find(x) != lo.end())
        {
            lo.erase(lo.find(x));
            rebalance();
            return;
        }
    }

    void rebalance()
    {
        if (!lo.empty() && !hi.empty() && *lo.rbegin() > *hi.begin())
        {
            ll x = *hi.begin();
            hi.erase(hi.find(x));
            lo.insert(x);
        }
        if (lo.size() > hi.size())
        {
            ll x = *lo.rbegin();
            lo.erase(lo.find(x));
            hi.insert(x);
        }
        if (lo.size() + 1 < hi.size())
        {
            ll x = *hi.begin();
            hi.erase(hi.find(x));
            lo.insert(x);
        }
    }

    ll get_median()
    {
        ll hi_sz = hi.size(), lo_sz = lo.size();
        ll sz = hi_sz + lo_sz;

        if (sz == 0)
        {
            return -1;
        }

        if (sz % 2 == 0)
        {
            ll md = *lo.rbegin() + *hi.begin();
            return (md * binExp(2, MOD - 2, MOD)) % MOD;
        }
        else
        {
            return *hi.begin();
        }
    }
};

struct sliding_mean
{
    multiset<ll> mt;
    ll sum = 0;
    void init()
    {
        mt.clear();
    }
    void insert(ll x)
    {
        sum = (sum + x) % MOD;
        mt.insert(x);
    }
    void remove(ll x)
    {
        sum = (sum - x + MOD) % MOD;
        mt.erase(mt.find(x));
    }
    ll get_mean()
    {
        if(mt.empty()){
            return -1;
        }
        ll sz = mt.size();
        ll res = (sum * binExp(sz, MOD - 2, MOD)) % MOD;
        return res;
    }
};

void solve()
{
    ll q;
    cin >> q;

    sliding_median md;
    sliding_mode mode;
    sliding_mean mn;
    while (q--)
    {
        string s;
        cin >> s;
        if (s == "insert")
        {
            ll x;
            cin >> x;
            md.insert(x);
            mode.insert(x);
            mn.insert(x);
        }
        if (s == "remove")
        {
            ll x;
            cin >> x;
            md.remove(x);
            mode.remove(x);
            mn.remove(x);
        }
        if (s == "getMedian")
        {
            cout << md.get_median() << endl;
        }
        if (s == "getMode")
        {
            cout << mode.get_mode() << endl;
        }
        if (s == "getMean")
        {
            cout << mn.get_mean() << endl;
        }
    }
}

int main()
{
    ll t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}