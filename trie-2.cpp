#include <bits/stdc++.h>
using namespace std;
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define nline "\n"
typedef long long ll;

/*
Problem:
Given an array of integers, find the maximum XOR value of any subarray.

Explanation:
The XOR of a subarray from index l to r can be represented as:
    prefix[r] ^ prefix[l - 1]
where prefix[i] is the XOR of elements from the start of the array to index i.

To efficiently find the maximum XOR for all subarrays, we:
1. Maintain a prefix XOR array.
2. insert prefix_xor[r] ([.....r]) and then find the best l for this to be maximum.

Input:
- The first line contains an integer t, the number of test cases.
- For each test case, the first line contains n, the size of the array.
- The second line contains n integers, the elements of the array.

Output:
- For each test case, print the maximum XOR value of any subarray.

Example Input:
3
5
1 2 3 4 5
6
7 14 6 8 6 65
5
74 14 5 6 9

Example Output:
7
79
78
*/

struct node
{
    node *left;  // 0 bit
    node *right; // 1 bit
    node()
    {
        left = nullptr;
        right = nullptr;
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
    }
    ll findMaxXor(ll num)
    {
        node *curr = root;
        ll ans = 0;
        for (ll i = 31; i >= 0; i--)
        {
            ll bit = ((num >> i) & 1);
            if (bit == 0)
            {
                if (curr->right != nullptr)
                {
                    curr = curr->right;
                    ans = (ans | (1 << i));
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {
                if (curr->left != nullptr)
                {
                    curr = curr->left;
                    ans = (ans | (1 << i));
                }
                else
                {
                    curr = curr->right;
                }
            }
        }
        return ans;
    }
};

void solve()
{
    ll n;
    cin >> n;
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
    tt.insert(0);
    for (ll l = 0; l < n; l++)
    {
        // prefix[r] ^ prefix[l - 1] = xor
        // finding best r for this l
        ans = max(ans, tt.findMaxXor(prefix_xor[l]));
        tt.insert(prefix_xor[l]);
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