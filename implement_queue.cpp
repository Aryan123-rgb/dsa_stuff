#include <bits/stdc++.h>
using namespace std;
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define nline "\n"
typedef long long ll;

/*
    Approach:
    We implement a queue using two stacks (st1 and st2).
    - push(x): Push the element onto st1.
    - pop(): If st2 is not empty, pop the top element from st2.
             Otherwise, transfer all elements from st1 to st2 and then pop.
    - front(): If st2 is not empty, return its top element.
               Otherwise, transfer all elements from st1 to st2 and return the top of st2.

    Intuition:
    A queue follows the FIFO (First In First Out) principle, whereas a stack follows LIFO (Last In First Out).
    Since we only have stacks, we need to simulate FIFO behavior using two stacks.
    - The first stack (st1) is used to store incoming elements.
    - The second stack (st2) helps reverse the order to mimic the behavior of a queue.
    - When popping or fetching the front element, if st2 is empty, we transfer all elements from st1 to st2,
      effectively reversing their order and making the first inserted element accessible.
    - This method ensures that push operations are O(1), while pop and front operations can be amortized O(1).
*/

struct my_queue
{
    stack<ll> st1, st2;

    // Push operation: Simply push the element into st1
    void push(ll x)
    {
        st1.push(x);
    }
    
    // Pop operation: 
    // If st2 is not empty, pop from it.
    // Otherwise, transfer elements from st1 to st2 and then pop.
    ll pop()
    {
        ll ans = -1;
        if (!st2.empty())
        {
            ans = st2.top();
            st2.pop();
        }
        else
        {
            while (!st1.empty())
            {
                ll y = st1.top();
                st1.pop();
                st2.push(y);
            }

            if (!st2.empty())
            {
                ans = st2.top();
                st2.pop();
            }
        }
        return ans;
    }
    
    // Front operation:
    // If st2 is not empty, return its top element.
    // Otherwise, transfer elements from st1 to st2 and return the top of st2.
    ll front()
    {
        if (!st2.empty())
        {
            return st2.top();
        }
        else
        {
            while (!st1.empty())
            {
                ll y = st1.top();
                st1.pop();
                st2.push(y);
            }
            return st2.top();
        }
    }
};

void solve()
{
    ll q;
    cin >> q;
    my_queue qu;
    while (q--)
    {
        string s;
        cin >> s;
        if (s == "push")
        {
            ll x;
            cin >> x;
            qu.push(x);
        }
        if (s == "pop")
        {
            cout << qu.pop() << nline;
        }
        if (s == "front")
        {
            cout << qu.front() << nline;
        }
    }
}

signed main()
{
    int t = 1;
    cin >> t;
    for (ll i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
