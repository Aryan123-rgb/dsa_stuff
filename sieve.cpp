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

const int N = 2e5 + 10;
vector<ll> isPrime(N, 1);
vector<ll> spf(N + 1, 0);
vector<ll> hpf(N + 1, 0);
vector<ll> prime;

void sieve()
{
    for (int i = 2; i < N; i++)
    {
        if (isPrime[i])
        {
            prime.push_back(i);
            spf[i] = hpf[i] = i;
            for (int j = 2 * i; j < N; j += i)
            {
                isPrime[j] = 0;
                hpf[j] = i;
                if (spf[j] == 0)
                {
                    spf[j] = i;
                }
            }
        }
    }
}

map<ll, ll> prime_factorise(ll n, vector<ll> &prime_factors)
{
    map<ll, ll> mp;
    while (n > 1)
    {
        ll prime_factor = spf[n];
        prime_factors.push_back(prime_factor);
        while (n % prime_factor == 0)
        {
            mp[prime_factor]++;
            n /= prime_factor;
        }
    }
    return mp;
}

// ll count_divisors(ll n)
// {
//     map<ll, ll> mp = prime_factorise(n);
//     ll cnt = 1;
//     for (auto &[prime, exp] : mp)
//     {
//         cnt = (cnt * (exp + 1)) % MOD;
//     }
//     return cnt;
// }

// ll sum_of_divisors(ll n)
// {
//     map<ll, ll> mp = prime_factorise(n);
//     ll sum = 0;
//     for (auto &[prime, exp] : mp)
//     {
//         ll c = exp + 1;
//         ll gp_sum = (pow(prime, c) - 1) / prime - 1;
//         sum *= gp_sum;
//     }
//     return sum;
// }

ll hsh[N];
ll present[N];

void solve()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        hsh[x]++;
    }
    // mark all the powers of x, x*x,x*x*x...

    // special case for 0, 1
    present[0] = hsh[0];
    present[1] = hsh[1];
    for (ll i = 2; i < N; i++)
    {
        if (hsh[i])
        {
            for (ll j = i; j < N; j *= i)
            {
                present[j] = 1;
            }
        }
    }
    while (q--)
    {
        ll x;
        cin >> x;
        vector<ll> prime_factors;
        map<ll, ll> mp = prime_factorise(x, prime_factors);
        ll fl = 0;
        for (ll i = 0; i < prime_factors.size(); i++)
        {
            for (ll j = i; j < prime_factors.size(); j++)
            {
                // reducing x = prime_factors[i] * prime_factors[j]
                ll a = prime_factors[i];
                ll b = prime_factors[j];
                if (a == b && mp[a] >= 2)
                {
                    ll product = a * b;
                    ll y = x / product;
                    if (present[y] == 1)
                    {
                        fl = 1;
                        break;
                    }
                }
                if (a != b && mp[a] >= 1 && mp[b] >= 1)
                {
                    ll product = a * b;
                    ll y = x / product;
                    if (present[y] == 1)
                    {
                        fl = 1;
                        break;
                    }
                }
            }
        }
        if (fl)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

int main()
{
    sieve();
    fastio();
    ll t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}