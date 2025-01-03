#include <bits/stdc++.h>
using namespace std;
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define nline "\n"
typedef long long ll;

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
        if(prefix_xor[l]<k){
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
