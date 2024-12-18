#include <bits/stdc++.h>
using namespace std;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define nline "\n"
#define all(x) (x).begin(), (x).end()
#define ll long long

/*
Question:
Given an empty collection of numbers, you need to process a sequence of queries of the following types:
1. "insert x": Insert the number `x` into the collection.
2. "remove x": Remove the number `x` from the collection (if it exists).
3. "sum": Print the sum of the top `k` largest numbers in the collection.

You are given the value of `k` and the number of queries `q`. Your task is to efficiently manage the collection and answer each query.

Constraints:
- The value of `k` is fixed and known beforehand.
- Queries are given in arbitrary order.

Intuition:
To solve this problem efficiently, we need to maintain the `k` largest elements in the collection, and their sum must be readily available for the "sum" query. 
We use a partitioning approach with two heaps:
1. `mt1` (multiset): This holds the `k` largest elements in the collection.
2. `mt2` (multiset): This holds the remaining `n-k` elements.

The key idea is to keep the size of `mt1` fixed to `k`. We adjust the elements between `mt1` and `mt2` during insertions and deletions to ensure `mt1` always holds the top `k` largest elements, while maintaining efficient updates and retrieval of the sum.

Approach:
1. **Insert**: 
   - Add the new element to `mt1` and update the sum.
   - If the size of `mt1` exceeds `k`, move the smallest element from `mt1` to `mt2` and adjust the sum.

2. **Remove**:
   - If the element exists in `mt1`, remove it and adjust the sum.
   - If it exists in `mt2`, simply remove it.
   - If the size of `mt1` becomes less than `k` (after removal), move the largest element from `mt2` to `mt1` and update the sum.

3. **Sum**:
   - Return the current sum of elements in `mt1`.

This approach ensures efficient management of the top `k` largest elements and supports all operations within logarithmic time complexity per query due to the use of multisets.
*/

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
    void insert(ll x)
    {
        mt1.insert(x);
        sum += x;

        if (mt1.size() > k)
        {
            ll sm = *mt1.begin();
            sum -= sm;
            mt2.insert(sm);
            mt1.erase(mt1.find(sm));
        }
    }
    void remove(ll x)
    {
        if (mt1.find(x) != mt1.end())
        {
            mt1.erase(mt1.find(x));
            sum -= x;
        }
        else if (mt2.find(x) != mt2.end())
        {
            mt2.erase(mt2.find(x));
        }

        if (mt1.size() < k && !mt2.empty())
        {
            ll lg = *mt2.rbegin();
            mt1.insert(lg);
            sum += lg;
            mt2.erase(mt2.find(lg));
        }
    }
    ll get_sum()
    {
        return sum;
    }
};

void solve()
{
    ll k, q;
    cin >> k >> q;

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
