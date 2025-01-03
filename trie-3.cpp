#include <bits/stdc++.h>
using namespace std;
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define nline "\n"
typedef long long ll;

/*
Question:
Given an array `v` of size `n` and an integer `k`, find the number of subarrays
whose XOR is less than `k`.

Explanation of the Solution:
1. **Prefix XOR**:
   - We use the concept of prefix XOR to represent the XOR of any subarray.
   - XOR of subarray `v[i...j]` can be calculated as `prefix_xor[j] ^ prefix_xor[i-1]`.

2. **Using a Trie**:
   - A trie is built to store the binary representation of prefix XOR values.
   - for each value of r we query how many l's are there for which xor of the subarray is less than K`.

3. **Key Steps**:
   - Make sure to insert r, after querying for r, because we only calculate in one direction, that is by inserting r and calculating optimal l's

4. **Time Complexity**:
   - Trie insertion/query operation takes `O(32)` for 32-bit integers.
   - For `n` elements, the complexity is `O(32 * n)` which is efficient.

5. **Edge Cases**:
   - Make sure to count to complete array [0.....r]

Example Input:
2
5 3
1 2 3 4 5
10 472156
645 45 8 6 45564 46868 89797 4566 65546 65467

Example Output:
8
55
*/

struct node
{
    node *left;  // 0 bit
    node *right; // 1 bit
    ll cnt_prefix, cnt_end;
    node()
    {
        left = nullptr;
        right = nullptr;
        cnt_prefix = cnt_end = 0;
    }
};

struct trie
{
    node *root;
    trie()
    {
        root = new node();
    }
    void insert(ll num)
    {
        node *curr = root;
        for (ll i = 31; i >= 0; i--)
        {
            curr->cnt_prefix++;
            ll bit = ((num >> i) & 1);
            if (bit == 0)
            {
                if (curr->left == nullptr)
                {
                    curr->left = new node();
                }
                curr = curr->left;
            }
            else
            {
                if (curr->right == nullptr)
                {
                    curr->right = new node();
                }
                curr = curr->right;
            }
        }
        curr->cnt_end++;
    }
    ll countSubarrayLessThanK(ll num, ll k)
    {
        node *curr = root;
        ll ans = 0;
        for (ll i = 31; i >= 0; i--)
        {
            ll kbit = ((k >> i) & 1);
            ll num_bit = ((num >> i) & 1);
            if (kbit == 0)
            {
                if (num_bit == 0)
                {
                    if (curr->left == nullptr)
                    {
                        break;
                    }
                    curr = curr->left;
                }
                else
                {
                    if (curr->right == nullptr)
                    {
                        break;
                    }
                    curr = curr->right;
                }
            }
            else
            {
                if (num_bit == 0)
                {
                    if (curr->left != nullptr)
                    {
                        ans += curr->left->cnt_prefix + curr->left->cnt_end;
                    }
                    if (curr->right == nullptr)
                    {
                        break;
                    }
                    curr = curr->right;
                }
                else
                {
                    if (curr->right != nullptr)
                    {
                        ans += curr->right->cnt_end + curr->right->cnt_prefix;
                    }
                    if (curr->left == nullptr)
                    {
                        break;
                    }
                    curr = curr->left;
                }
            }
        }
        return ans;
    }
};

void solve()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<ll> prefix_xor(n);
    prefix_xor[0] = v[0];
    ll ans = 0;
    for (ll i = 1; i < n; i++)
    {
        prefix_xor[i] = (prefix_xor[i - 1] ^ v[i]);
    }
    trie tt;
    for (ll l = 0; l < n; l++)
    {
        ans += tt.countSubarrayLessThanK(prefix_xor[l], k);
        tt.insert(prefix_xor[l]);
        if (prefix_xor[l] < k)
        {
            ans++;
        }
    }
    cout << ans << nline;
}

int main()
{
    fastio();
    ll t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
