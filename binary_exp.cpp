#include <bits/stdc++.h>
using namespace std;
#define ll long long

// a <= 10^9, b <= 10^9, mod <= 10^18
// Time Complexity - O(log log b)
ll binExp(ll a, ll b, ll mod)
{
    // if a exceeds mod do a%=mod before proceeding
    ll ans = 1;
    while (b)
    {
        if (b & 1LL)
        {
            ans = binMultiply(ans, a, mod);
        }
        a = binMultiply(a, a, mod);
        b >>= 1;
    }
    return ans;
}

// Time Complexity - O(log b)
// if we have to calculate a * b and a,b <= 1e18
ll binMultiply(ll a, ll b, ll mod)
{
    ll ans = 0;
    while (b)
    {
        if (b & 1)
        {
            ans = (ans + a) % mod;
        }
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

signed main()
{
    // Euler's Theorem:
    // If a and M are coprime, then: a^phi(M) ≡ 1 (mod M)
    // So, a^b ≡ a^(b % phi(M)) (mod M) when b is very large
    // General Case:
    // If M is prime, then phi(M) = M - 1
    // For nested exponentiation like a ^ b ^ c % M,
    // Reduce it as: a ^ (b ^ c % phi(M)) % M

    // Fermat's Little Theorem:
    // Ifa and M are coprime,
    // Then: a^(M - 1) ≡ 1 (mod M)
    // => a^(M - 2) ≡ a^(-1) (mod M)
    // So, the modular inverse of a under modulo M is: a^(M - 2) % M
    // nck % M = n! / (k! * (n - k)!) % M
    // nck % M = (n! * inverse(k! * (n - k)!)) % M
}

