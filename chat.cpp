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
#define debug(x)         \
    cerr << #x << nline; \
    _print(x);           \
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
        cerr << nline;
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
        cerr << nline;
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
        cerr << nline;
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
        cerr << nline;
    }
    cerr << "]";
}

const int N = 1e4 + 10;

set<ll> prime_numbers;

void sieve()
{
    vector<ll> isPrime(N, true);
    for (ll i = 2; i < N; i++)
    {
        if (isPrime[i])
        {
            prime_numbers.insert(i);
            for (ll j = i * i; j < N; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}

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
    void insert(ll num)
    {
    }
    void remove(ll num)
    {
    }
    ll get_sum()
    {
    }
};

void solve()
{
    int k;
    cin >> k;
    ll q;
    cin >> q;
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