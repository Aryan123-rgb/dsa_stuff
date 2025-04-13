#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:

Given an undirected graph with N nodes and M edges, determine the number of connected components that would result after removing each node (from 0 to N-1) one at a time. For each node, output the total number of connected components formed after its removal.

Note:
- The graph is 0-indexed.
- The graph is connected initially or may consist of multiple components.
*/

vector<vector<int>> adj;
vector<int> vis, tin, low;
vector<int> vec; // vec[i] -> the total increase in connected components after deleting ith node
int timer = 1;

void dfs(int node, int parent = 0)
{
    vis[node] = 1;
    tin[node] = low[node] = timer++;
    int children = 0;
    vector<int> childs;
    for (auto neigh : adj[node])
    {
        if (!vis[neigh])
        {
            children++;
            dfs(neigh, node);
            childs.push_back(neigh);
            low[node] = min(low[node], low[neigh]);
        }
        else if (neigh != parent)
        {
            low[node] = min(low[node], tin[neigh]);
        }
    }

    if (parent == 0)
    {
        vec[node] = children - 1;
    }
    else
    {
        for (auto &neigh : childs)
        {
            if (low[neigh] >= tin[node])
            {
                vec[node]++;
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vis.assign(n + 1, 0);
    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    vec.assign(n + 1, 0);

    int totalComponent = 0;

    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            totalComponent++;
            dfs(i);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout  << i << ": " << vec[i] + totalComponent << endl;
    }

    return 0;
}
