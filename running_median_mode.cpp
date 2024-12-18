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
Implement a data dashboard that supports efficient computation of statistical measures such as:
1. Mean
2. Variance
3. Median
4. Mode

The dashboard should allow dynamic insertion and deletion of elements while maintaining efficient updates of the measures.

Operations:
- `insert(x)`: Add the element `x` to the dataset.
- `remove(x)`: Remove the element `x` from the dataset.
- `get_mean()`: Return the mean of the current dataset.
- `get_variance()`: Return the variance of the current dataset.
- `get_mode()`: Return the mode of the current dataset.
- `get_median()`: Return the median of the current dataset.

Requirements:
- All operations should be efficient, ideally logarithmic for updates and constant for retrieval of statistics.

Solution Overview:
The solution uses the following techniques:
1. **Mean and Variance**: Use simple arithmetic with cumulative sums and counts to compute these dynamically.
2. **Mode**: Use a frequency map to track occurrences of each element and a multiset to maintain the order of frequencies.
3. **Median**: Use two heaps (implemented as multisets) to partition the dataset into low and high halves, ensuring efficient median updates.
*/

struct data_dashboard
{
    // --- Variables for Mean and Variance ---
    double sum = 0, sum_sq = 0;
    ll cnt = 0;

    // --- Variables for Mode ---
    map<ll, ll> freq;                  // Frequency map for each element
    multiset<pair<ll, ll>> freq_order; // Multiset to maintain order of frequencies

    // --- Variables for Median ---
    multiset<ll> hi, lo; // Two multisets: lo (lower half) and hi (upper half)

    /*
    --- Insert Operation ---
    Inserts an element `x` into the dataset. Updates:
    1. Mean and variance values by updating `sum`, `sum_sq`, and `cnt`.
    2. Mode by updating the frequency map and ordered frequency multiset.
    3. Median by inserting the element into the appropriate partition (low or high) and rebalancing the heaps.
    */
    void insert(ll x)
    {
        // Update for mean and variance
        sum += x;
        sum_sq += (x * x);
        cnt++;

        // Update for mode
        if (freq_order.find({freq[x], x}) != freq_order.end())
        {
            freq_order.erase(freq_order.find({freq[x], x}));
        }
        freq[x]++;
        freq_order.insert({freq[x], x});

        // Update for median
        if (lo.empty() || x <= *lo.rbegin())
        {
            lo.insert(x);
        }
        else
        {
            hi.insert(x);
        }
        rebalance();
    }

    /*
    --- Remove Operation ---
    Removes an element `x` from the dataset. Updates:
    1. Mean and variance values by updating `sum`, `sum_sq`, and `cnt`.
    2. Mode by updating the frequency map and ordered frequency multiset.
    3. Median by removing the element from the appropriate partition and rebalancing the heaps.
    */
    void remove(ll x)
    {
        // Update for mean and variance
        sum -= x;
        sum_sq -= (x * x);
        cnt--;

        // Update for mode
        if (freq_order.find({freq[x], x}) != freq_order.end())
        {
            freq_order.erase(freq_order.find({freq[x], x}));
        }
        freq[x]--;
        if (freq[x] > 0)
        {
            freq_order.insert({freq[x], x});
        }

        // Update for median
        if (lo.find(x) != lo.end())
        {
            lo.erase(lo.find(x));
        }
        else if (hi.find(x) != hi.end())
        {
            hi.erase(hi.find(x));
        }
        rebalance();
    }

    /*
    --- Rebalance Heaps ---
    Ensures that the size of the lower half (`lo`) is either equal to or one greater than the size of the upper half (`hi`).
    */
    void rebalance()
    {
        if (lo.size() < hi.size())
        {
            ll x = *hi.begin();
            hi.erase(hi.find(x));
            lo.insert(x);
        }
        else if (lo.size() > hi.size() + 1)
        {
            ll x = *lo.rbegin();
            lo.erase(lo.find(x));
            hi.insert(x);
        }
    }

    /*
    --- Mean ---
    Returns the mean of the dataset.
    Formula: Mean = Sum / Count
    */
    double get_mean()
    {
        return (double)sum / (double)cnt;
    }

    /*
    --- Variance ---
    Returns the variance of the dataset.
    Formula: Variance = (Sum of squares / Count) - (Mean)^2
    */
    double get_variance()
    {
        return sum_sq / cnt - (get_mean() * get_mean());
    }

    /*
    --- Mode ---
    Returns the mode of the dataset.
    Uses the frequency map and frequency-order multiset to track the element with the highest frequency.
    */
    ll get_mode()
    {
        auto x = *freq_order.rbegin();
        return x.second;
    }

    /*
    --- Median ---
    Returns the median of the dataset.
    - If the count is odd, median is the largest element of the lower half (`lo`).
    - If the count is even, median is the average of the largest element of the lower half (`lo`) and the smallest element of the upper half (`hi`).
    */
    double get_median()
    {
        if (cnt % 2 == 0)
        {
            double x = *hi.begin();
            double y = *lo.rbegin();
            return (x + y) / 2.0;
        }
        else
        {
            return *lo.rbegin();
        }
    }
};

void solve()
{
    data_dashboard ddb;
    ddb.insert(1);
    ddb.insert(2);
    ddb.insert(4);
    cout << ddb.get_mean() << nline;     // Output: 2.333...
    cout << ddb.get_median() << nline;   // Output: 2
    cout << ddb.get_variance() << nline; // Output: 1.555...
    cout << ddb.get_mode() << nline;     // Output: 1 (all elements have the same frequency, so any is valid)
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
