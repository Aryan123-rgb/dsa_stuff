#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Time Complexity -> O(N log log N)
// For most optimal we start the second loop from (i * i), because all the multiples before that
// would have already been marked

// for example i = 5, we start from 25 ignoring 10, 15, 20 because 10, 20 would have been
// marked by 2 and 15 would have been marked by 3
vector<ll> sieve(ll N = 1e7)
{
    vector<bool> is_prime(N + 1, true);
    vector<ll> primes;
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= N; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
            for (ll j = i * i; j <= N; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

// We need to find prime numbers in the range [a,b] where
// 0 < a <= b <= 1e12
// b - a <= 1e6

vector<ll> segmented_sieve(ll L, ll R)
{
    // 1. use sieve to precompute primes in range R [1.....sqrt(R)] as base primes
    vector<ll> base_primes(sieve(ceil(sqrt(R))));

    // 2. sieve the range L to R using the primes found in range [1....sqrt(R)]
    vector<bool> is_prime(R - L + 1, true);
    if (L == 1)
        is_prime[0] = false;

    for (auto prime : base_primes)
    {
        // find first number >= L which is the multiple of prime
        ll ceil_by_p = (L + prime - 1) / prime;
        ll curr_mul = prime * ceil_by_p;
        curr_mul = max(curr_mul, prime * prime);

        // strike off all it's multiple in the range
        while (curr_mul <= R)
        {
            is_prime[curr_mul - L] = false;
            curr_mul += prime;
        }
    }

    // 3. Store the prime and return
    vector<ll> primes_l_to_r;
    for (ll i = 0; i < R - L + 1; i++)
    {
        if (is_prime[i])
        {
            primes_l_to_r.push_back(i + L);
        }
    }

    return primes_l_to_r;
}

// We will be given Q queries and in each query a number X
// we have to find the prime factors of X, for example X = 60 -> 2,2,3,5
// 1 <= Q <= 1e6
// 1 <= X <= 1e6

// Creating the S.P (smallest prime) array
// We cannot use (i * i) optimisation here so this array cannot be build for 1e7 constraints
// Time Complexity = O(N log log N)
vector<ll> spf;
void create_spf(ll N = 1e6)
{
    spf.assign(N + 1, 1);
    for (ll i = 2; i <= N; i++)
    {
        spf[i] = i;
    }
    for (ll i = 2; i <= N; i++)
    {
        if (spf[i] == i)
        {
            for (ll j = 2 * i; j <= N; j += i)
            {
                if (spf[j] == j)
                {
                    spf[j] = i;
                }
            }
        }
    }
}

// Time complexity = O(log X)
vector<ll> prime_factors(ll x)
{
    // precompute spf array before processing this
    vector<ll>ans;
    while(x > 1){
        ans.push_back(spf[x]);
        x /= spf[x];
    }
    return ans;
}
// X = (p1 ^ a1) * (p2 ^ a2) * (p3 ^ a3)....... prime factors

// S1(X) -> Total count of divisors of X
// S1(X) = (1 + a1) * (1 + a2) * (1 + a3)......

// S2(x) -> Total sum of divisors of X
// S2(X) -> (p1 ^ (a1 + 1) - 1) / (p1 - 1) + ....... G.P sum