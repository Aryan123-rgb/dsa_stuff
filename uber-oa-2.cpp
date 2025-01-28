#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using namespace std;

#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long long ll;
vector<vector<pair<ll, ll>>> g;
vector<ll> dis, vis;

void dijikstra(ll src)
{
    priority_queue<pair<ll, ll>> pq;
    pq.push({0, src});
    dis[src] = 0;

    while (!pq.empty())
    {
        ll node = pq.top().second;
        pq.pop();

        if (vis[node])
            continue;
        vis[node] = 1;

        for (auto &v : g[node])
        {
            ll neigh = v.first, wt = v.second;
            if (dis[neigh] > dis[node] + wt)
            {
                dis[neigh] = dis[node] + wt;
                pq.push({-dis[neigh], neigh});
            }
        }
    }
}

void solve()
{
    ll n, b, a;
    cin >> n >> b >> a;
    map<ll, vector<ll>> mp;
    for (ll i = 1; i <= n; i++)
    {
        ll x;
        cin >> x;
        mp[x].push_back(i);
    }
    ll src;
    cin >> src;
    ll d = mp.size(); // distinct number
    g.resize(n + d + 1);
    dis.assign(n + d + 1, 1e18);
    vis.assign(n + d + 1, 0);

    // adding adjacent edges (bi-directional edges)
    for (ll i = 1; i < n; i++)
    {
        g[i].push_back({i + 1, a});
        g[i + 1].push_back({i, a});
    }
    // adding every node to it's respecitve supernode
    // supernode will be n+1,n+2,n+3...
    ll superNode = n + 1;
    for (auto &v : mp)
    {
        for (auto &u : v.second)
        {
            g[u].push_back({superNode, 0});
            g[superNode].push_back({u, b});
        }
        superNode++;
    }
    dijikstra(src);
    for (ll i = 1; i <= n; i++)
    {
        cout << dis[i] << " ";
    }
    cout << endl;
}

signed main()
{
    fast;
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}