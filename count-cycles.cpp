/*
Question:
Count all simple cycles in an undirected graph using a memoized DFS with bitmasking.
The graph uses 1-based indexing for nodes. To avoid counting the same cycle in different rotations or directions,
the DFS enforces an ordering constraint: only neighbors with values greater than or equal to the starting node are considered.
Each cycle is counted twice (once in each direction), so the final result is divided by 2.

Explanation:
This program reads an undirected graph and uses a recursive depth-first search (DFS) with memoization to count the number of simple cycles.
A bitmask is used to track visited nodes. For each starting node, a separate DP table is created since the starting node is part of the state.
Cycles are only considered if they contain at least three nodes and return to the starting node. The ordering constraint (only considering neighbors
with a value greater than or equal to the starting node) ensures that cycles are rooted at their smallest node and are not overcounted.
Finally, since each cycle is counted twice (once in each direction), the total is divided by 2 before outputting the result.
*/

// #include <iostream>
// #include <vector>
// using namespace std;

// using ll = long long;

// int n, m;
// vector<vector<int>> g;

// ll rec(int node, ll mask, int start, vector<vector<ll>> &memo) {
//     mask = mask | (1LL << node);
//     int visited = __builtin_popcountll(mask);
//     if (memo[node][mask] != -1)
//         return memo[node][mask];

//     ll count = 0;
//     for (int neigh : g[node]) {
//         if (neigh < start)
//             continue;
//         if (neigh == start && visited > 2) {
//             count++;
//             continue;
//         }
//         if ((mask >> neigh) & 1LL)
//             continue;
//         count += rec(neigh, mask, start, memo);
//     }
//     return memo[node][mask] = count;
// }

// void solve() {
//     cin >> n >> m;
//     g.resize(n + 1);
//     for (int i = 0; i < m; i++) {
//         int a, b;
//         cin >> a >> b;
//         g[a].push_back(b);
//         g[b].push_back(a);
//     }

//     ll ans = 0;
//     for (int start = 1; start <= n; start++) {
//         vector<vector<ll>> memo(n + 1, vector<ll>(1 << (n + 1), -1));
//         ans += rec(start, 0, start, memo);
//     }
//     cout << ans / 2 << "\n";
// }

// int main() {
//     solve();
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
int curr;
int isEdge[20][20]; // consider 0 based indexing
int dp[20][1 << 20];
int rec(int i, int mask, int sz)
{
    // number of simple cycles containing i; not containing cur - 1, cur - 2, ..., 1 since those cases already calculated; avoids overcounting
    // alt def: number of cycles starting/ending at curr, containing i
    // hence possible transitions will always be cur, cur + 1, ...
    // need to include size as a paremeter, to check base case, not necessary in dp table
    // base
    // no base case (or no return statement in base case)
    // cache
    if (dp[i][mask] != -1)
        return dp[i][mask];
    // compute
    int ans = 0;
    if (isEdge[curr][i] && sz > 2)
    {
        // one possible combination
        ans++;
    }
    for (int j = curr; j < n; j++)
    {
        if (mask & (1 << j))
            continue;
        // since we are using adj matrix, hence different way to iterate
        if (isEdge[i][j])
        {
            ans += rec(j, mask | (1 << j), sz + 1);
        }
    }
    // save
    return dp[i][mask] = ans;
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        isEdge[a][b] = isEdge[b][a] = 1;
        // remember how to fill adj mtrx
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        curr = i;
        memset(dp, -1, sizeof(dp));
        ans += rec(curr, (1 << curr), 1);
    }
    cout << ans / 2;
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
}
