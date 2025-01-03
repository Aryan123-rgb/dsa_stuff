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
You are given a series of operations on a trie data structure to maintain a collection of integers. 
The operations include:
- Adding an integer to the collection.
- Removing an integer from the collection.
- Querying the maximum XOR of a given integer with any integer in the collection.

Input:
The first line contains an integer n, the number of operations.
Each of the next n lines contains an operation:
- "? x": Find the maximum XOR of x with any integer in the collection.
- "+ x": Add x to the collection.
- "- x": Remove x from the collection.

Example Input:
12
? 4
+ 4
? 4
+ 4
? 3
- 4
- 4
? 3
+ 4
? 4
+ 1
+ 1

Output for Example Input:
4
0
7
7
4
*/

struct node
{
    node *left;  // 0 bit
    node *right; // 1 bit
    ll cnt_prefix;
    ll cnt_end;
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
        curr->cnt_prefix++;
        curr->cnt_end++;
    }
    void remove(ll num)
    {
        node *curr = root;
        for (ll i = 31; i >= 0; i--)
        {
            curr->cnt_prefix--;
            ll bit = ((num >> i) & 1);
            if (bit == 0)
            {
                if (curr->left == nullptr)
                {
                    return;
                }
                curr = curr->left;
            }
            else
            {
                if (curr->right == nullptr)
                {
                    return;
                }
                curr = curr->right;
            }
        }
        curr->cnt_prefix--;
        curr->cnt_end--;
    }
    ll findMaxXor(ll num)
    {
        ll ans = 0;
        node *curr = root;
        for (ll i = 31; i >= 0; i--)
        {
            ll bit = ((num >> i) & 1);
            if (bit == 0)
            {
                if (curr->right != nullptr && curr->right->cnt_prefix > 0)
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
                if (curr->left != nullptr && curr->left->cnt_prefix > 0)
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
    trie tt;
    tt.insert(0);
    for (ll i = 0; i < n; i++)
    {
        char ch;
        ll x;
        cin >> ch >> x;
        if (ch == '?')
        {
            cout << tt.findMaxXor(x) << nline;
        }
        else if (ch == '+')
        {
            tt.insert(x);
        }
        else
        {
            tt.remove(x);
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
