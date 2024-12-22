#include <bits/stdc++.h>
using namespace std;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define nline "\n"
#define all(x) (x).begin(), (x).end()
#define ll long long

struct range_maintenance
{
    set<pair<ll, ll>> st;
    void fill_range(ll l, ll r)
    {
        // we are finding less than equal to l
        auto it = st.upper_bound({l, 1e9});
        if (it != st.begin())
        {
            it--;
            if (it->second >= l)
            {
                l = it->first;
                r = max(r, it->second);
                st.erase(it);
            }
        }

        it = st.upper_bound({r, 1e9});
        if (it != st.begin())
        {
            it--;
            if (it->second >= r)
            {
                r = it->second;
                l = min(l, it->first);
                st.erase(it);
            }
        }

        while (1)
        {
            it = st.lower_bound({l, 0});
            if (it == st.end() || (it->first > r))
            {
                break;
            }
            st.erase(it);
        }

        st.insert({l, r});
    }
    void clear_range(ll l, ll r)
    {
        auto it = st.upper_bound({l, 1e9});
        if (it != st.begin())
        {
            it--;
            if (it->second >= r)
            {
                ll lo1 = it->first;
                ll hi1 = l;

                ll lo2 = r;
                ll hi2 = it->second;

                st.erase(it);
                st.insert({lo1, hi1});
                st.insert({lo2, hi2});
                return;
            }
            if (it->second >= l)
            {
                ll lo = it->first;
                ll hi = l;
                st.erase(it);
                st.insert({lo, hi});
            }
        }

        it = st.upper_bound({r, 1e9});
        if (it != st.begin())
        {
            it--;
            if (it->second >= r)
            {
                ll lo = r;
                ll hi = it->second;
                st.erase(it);
                st.insert({lo, hi});
            }
        }

        while (1)
        {
            it = st.lower_bound({l, 0});
            if (it == st.end() || (it->first) >= r)
            {
                break;
            }
            st.erase(it);
        }
    }

    bool check_point(ll x)
    {
        // finding the first l <= x -> find upper bound - 1
        auto it = st.upper_bound({x, 1e9});

        if (it == st.begin())
        {
            return 0;
        }
        else
        {
            --it;
            // the current range either starts from x or starts before x => l <= x
            // Check if 'x' lies within the range [l, r].
            ll r = it->second;
            if (r >= x)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    // Check if all bulbs in the range [x, y] are active.
    bool check_range_all(ll x, ll y)
    {
        // finding the first l <= x -> find upper bound - 1
        auto it = st.upper_bound({x, 1e9});

        if (it == st.begin())
        {
            return 0;
        }
        else
        {
            --it;

            // the current range either starts from x or starts before x => l <= x
            // Check if 'r' is greater than y
            ll r = it->second;
            if (r >= y)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    // Check if any bulb in the range [x, y] is active.
    bool check_range_any(ll x, ll y)
    {
        // Find the l strictly greater than 'x'.
        auto it = st.upper_bound({x, 1e9});

        // now there is a range that starts after x, if this range also starts before y
        ll l = it->first;
        // here l > x && l <= y , this range lies in the interval [x,y]
        if (it != st.end() && l <= y)
        {
            return 1;
        }

        // if any range overlaps x point only
        return check_point(x);
    }

    void print()
    {
        cout << "Current Status: ";
        for (auto v : st)
        {
            cout << "(" << v.first << "," << v.second << "), ";
        }
        cout << endl;
    }
};

void solve()
{
    ll q;
    cin >> q;
    range_maintenance rm;
    while (q--)
    {
        ll type;
        cin >> type;
        if (type == 1)
        {
            ll l, r;
            cin >> l >> r;
            rm.fill_range(l, r);
        }
        if (type == 2)
        {
            ll l, r;
            cin >> l >> r;
            rm.clear_range(l, r);
        }
        if (type == 3)
        {
            ll x;
            cin >> x;
            cout << rm.check_point(x) << endl;
        }
        if (type == 4)
        {
            ll l, r;
            cin >> l >> r;
            cout << rm.check_range_any(l, r) << endl;
        }
        rm.print();
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
