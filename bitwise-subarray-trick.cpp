#include <bits/stdc++.h>

using namespace std;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x)       \
    cerr << #x << " "; \
    _print(x);         \
    cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(ull t) { cerr << t; }

template <class T, class V>
void _print(pair<T, V> p);
template <class T>
void _print(vector<T> v);
template <class T>
void _print(set<T> v);
template <class T, class V>
void _print(map<T, V> v);
template <class T>
void _print(multiset<T> v);
template <class T, class V>
void _print(pair<T, V> p)
{
    cerr << "{";
    _print(p.ff);
    cerr << ",";
    _print(p.ss);
    cerr << "}";
}
template <class T>
void _print(vector<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(set<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(multiset<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T, class V>
void _print(map<T, V> v)
{
    cerr << "[ ";
    for (auto i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}

static bool cmp(pair<ll, ll> &p1, pair<ll, ll> &p2)
{
    return p1.second < p2.second;
}

void solve()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    map<ll, ll> prev_ends;
    map<ll, ll> freq;
    for (ll i = n - 1; i >= 0; i--)
    {
        map<ll, ll> new_ends;
        for (auto [x, y] : prev_ends)
        {
            ll n_value = gcd(v[i], x);
            new_ends[n_value] = max(new_ends[n_value], y);
        }
        new_ends[v[i]] = max(new_ends[v[i]], i);
        prev_ends = new_ends;

        cout << "Index at " << i << endl;
        for (auto v : prev_ends)
        {
            cout << v.first << " " << v.second << endl;
        }
        cout << endl;

        vector<pair<ll, ll>> vp(new_ends.begin(), new_ends.end());
        sort(vp.begin(), vp.end(), cmp);

        // cout << "Start at " << i << endl;
        for (ll j = 0; j < vp.size(); j++)
        {
            if (j == 0)
            {
                // range [i....vp[j].second] -> vp[j].first
                freq[vp[j].first] += (vp[j].second - i + 1);
                // cout << "Range [" << i << " " << vp[j].second << "] -> " << vp[j].first << nline;
            }
            else
            {
                // range [vp[j-1].second+1 , vp[j].second] -> vp[j].first
                freq[vp[j].first] += vp[j].second - vp[j - 1].second;
                // cout << "Range [" << vp[j - 1].second + 1 << " " << vp[j].second << "] -> " << vp[j].first << nline;
            }
        }
        // cout << nline;
    }
    // cout << freq[k] << endl;
}

int main()
{
    fastio();
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}