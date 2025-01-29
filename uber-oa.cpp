#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using namespace std;
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long long ll;

ll n, m;
ll st_node, en_node, k;
vector<vector<pair<ll, ll>>> g;
vector<vector<ll>> dis, vis;
vector<ll> c;
void dijikstra()
{
    dis.assign(n + 1, vector<ll>(k + 1, 1e18));
    vis.assign(n + 1, vector<ll>(k + 1, 0));
    priority_queue<pair<ll, pair<ll, ll>>> pq;
    pq.push({0, {st_node, 0}});
    dis[st_node][0] = 0;

    while (!pq.empty())
    {
        auto it = pq.top();
        pq.pop();

        ll curr_cost = -it.first;
        ll node = it.second.first;
        ll fuel = it.second.second;

        if (vis[node][fuel])
            continue;
        vis[node][fuel] = 1;

        // try and go to neighbour
        for (auto v : g[node])
        {
            ll neigh = v.first;
            ll fuel_req = v.second;

            // we can go to neighbours
            if (fuel >= fuel_req)
            {
                ll nfuel = fuel - fuel_req;
                ll ncost = curr_cost + 0;
                if (dis[neigh][nfuel] > ncost)
                {
                    dis[neigh][nfuel] = ncost;
                    pq.push({-ncost, {neigh, nfuel}});
                }
            }
        }

        // refill
        if (fuel + 1 <= k)
        {
            ll nfuel = fuel + 1;
            ll ncost = curr_cost + c[node];
            if (dis[node][nfuel] > ncost)
            {
                dis[node][nfuel] = ncost;
                pq.push({-ncost, {node, nfuel}});
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    g.resize(n + 1);
    c.resize(n + 1);

    for (ll i = 0; i < m; i++)
    {
        ll u, v, d;
        cin >> u >> v >> d;
        g[u].push_back({v, d});
        g[v].push_back({u, d});
    }

    for (ll i = 1; i <= n; i++)
    {
        cin >> c[i];
    }
    cin >> st_node >> en_node >> k;
    dijikstra();

    ll ans = 1e18;
    for (ll i = 0; i <= k; i++)
    {
        ans = min(ans, dis[en_node][i]);
    }
    cout << ans << endl;
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