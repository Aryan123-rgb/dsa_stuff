/*
Problem: Hamiltonian Walk

Given an undirected graph with 'n' nodes and 'm' edges, count all distinct paths 
that start at node 1, visit every node exactly once, and end at node 'n'.

Approach:
- Use DFS with bitmasking to track visited nodes.
- The bitmask represents the set of visited nodes.
- Recursively explore all possible paths from the current node.
- If all nodes have been visited and the current node is 'n', count the path.

Input:
- First line: Two integers 'n' and 'm' (1 ≤ n ≤ 20, 0 ≤ m ≤ n*(n-1)/2)
- Next 'm' lines: Two integers u, v representing an undirected edge between nodes u and v.

Output:
- A single integer representing the count of valid Hamiltonian walks.
*/

#include <iostream>
#include <vector>
using namespace std;

int n, m;
int mod = 1e9 + 7;
vector<vector<int>> adj;
vector<vector<int>> dp;

int dfs(int node, int mask) {
    if (mask == (1 << n) - 1) return node == n ? 1 : 0;

    // optimisation, if nth node (last node) is visited before the rest of the nodes
    if ((mask >> (n - 1)) & 1) return 0;
    
    if (dp[node][mask] != -1) return dp[node][mask];

    int count = 0;
    for (int neighbor : adj[node]) {
        if (mask & (1 << (neighbor - 1))) continue;
        count = (count + dfs(neighbor, mask | (1 << (neighbor - 1)))) % mod;
    }
    
    return dp[node][mask] = count;
}

int main() {
    cin >> n >> m;
    adj.resize(n + 1);
    dp.assign(n + 1, vector<int>(1 << n, -1));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    cout << dfs(1, 1 << 0) << endl;
    return 0;
}
