#include <bits/stdc++.h>
#include <iostream>
#include <cmath>

using namespace std;

#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
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

// for loops
#define get(v)                             \
    for (int i = 0; i < (ll)v.size(); i++) \
    cin >> v[i]

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
    cerr << "]" << endl;
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

long long int modInverse(long long int value, long long int mod)
{
    if (value == 1)
        return 1;
    return (mod - ((mod / value) * modInverse(mod % value, mod)) % mod + mod) % mod;
}

ll modPow(ll base, ll exponent)
{
    if (exponent == 0)
        return 1;
    if (exponent == 1)
        return base % MOD;

    ll halfPower = modPow(base, exponent / 2);
    if (exponent % 2 == 0)
        return (halfPower * halfPower) % MOD;
    else
        return (((halfPower * halfPower) % MOD) * base) % MOD;
}

const int N = 1e5 + 10;
vector<ll> isPrime(N, 1);
vector<ll> spf(N + 1, 0);
vector<ll> hpf(N + 1, 0);
vector<ll> prime;
bool isDone = false;

void sieve()
{
    if (isDone)
    {
        return;
    }
    isDone = true;
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

map<ll, ll> prime_factorise(ll n)
{
    map<ll, ll> mp;
    while (n > 1)
    {
        ll prime_factor = spf[n];
        while (n % prime_factor == 0)
        {
            mp[prime_factor]++;
            n /= prime_factor;
        }
    }
    return mp;
}

ll count_divisors(ll n, map<ll, ll> &mp)
{
    ll cnt = 1;
    for (auto &[prime, exp] : mp)
    {
        cnt = (cnt * (exp + 1)) % MOD;
    }
    return cnt;
}

ll sum_of_divisors(ll n, map<ll, ll> &mp)
{
    ll sum = 1;
    for (auto &[prime, exp] : mp)
    {
        ll c = exp + 1;
        ll numerator = (modPow(prime, exp + 1) - 1 + MOD) % MOD;
        ll inverseDenominator = modInverse(prime - 1, MOD);
        ll res = (numerator * inverseDenominator) % MOD;
        sum *= res;
    }
    return sum;
}

void solve()
{
    ll n;
    cin >> n;
    map<ll, ll> prime_factors = prime_factorise(n);
    cout << count_divisors(n, prime_factors) << " " << sum_of_divisors(n, prime_factors);
}

signed main()
{
    sieve();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}