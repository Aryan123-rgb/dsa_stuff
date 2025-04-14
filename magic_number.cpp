#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*

Problem Statement:
You are given two integers L and R represented as strings, and two more integers M and D.

Count how many magic numbers X exist in the range [L, R] (inclusive) such that:
1. X is divisible by M (i.e., X % M == 0).
2. The digits of X follow a specific pattern:
   - The number X should contain number D at even places or there should only be number D at even
   - positions
   - The digits of X at **even positions (1-based)** must be equal to D.

Input:
- t: number of test cases
- For each test case:
  - M D
  - L (as a string)
  - R (as a string)

Output:
- For each test case, print the number of valid integers satisfying the above conditions.

Example Input:
3
2 4
10
90
3 9
200
300
2 1
10 
90

Example Output:
7
3
0

Key idea: 
Instead of storing the whole number being formed (which could be large), we only track its remainder modulo M.
This is done using the formula:
    nextNum = (num * 10 + i) % M;

Explanation:
- Suppose the current number (so far) has remainder `num` modulo M.
- After appending a digit `i`, the new number is: (num_so_far * 10 + i)
- To track its remainder:
      new_remainder = (num * 10 + i) % M

We only care about numbers whose final remainder is 0 → which means divisible by M.
At base case (when all digits are placed), we check:
    if (num == 0) return 1 (valid number)
    else return 0

*/

ll MOD = 1e9 + 7;
ll M, D, len;
string L, R;
ll dp[2010][2][2][2010][3];

ll rec(ll index, ll lfl, ll rfl, ll num, ll pos) {
    if(index == len) {
        return (num == 0);
    }

    if(dp[index][lfl][rfl][num][pos] != -1)
        return dp[index][lfl][rfl][num][pos];

    ll lnum = L[index] - '0', rnum = R[index] - '0';
    ll start = lfl ? lnum : 0;
    ll end = rfl ? rnum : 9;

    ll ans = 0;
    for(ll i = start; i <= end; i++) {
        ll nlfl = (lfl && i == lnum);
        ll nrfl = (rfl && i == rnum);
        ll nextNum = (num * 10 + i) % M;

        if(pos == 0) {
            if(i == 0) {
                ans = (ans + rec(index + 1, nlfl, nrfl, nextNum, 0)) % MOD;
            } else {
                if(i == D) continue; // first non-zero can't be D (odd)
                ans = (ans + rec(index + 1, nlfl, nrfl, nextNum, 2)) % MOD;
            }
        }
        else if(pos == 1) { // odd pos → can't be D
            if(i == D) continue;
            ans = (ans + rec(index + 1, nlfl, nrfl, nextNum, 2)) % MOD;
        }
        else if(pos == 2) { // even pos → must be D
            if(i != D) continue;
            ans = (ans + rec(index + 1, nlfl, nrfl, nextNum, 1)) % MOD;
        }
    }

    return dp[index][lfl][rfl][num][pos] = ans;
}

void solve() {
    cin >> M >> D >> L >> R;
    L.insert(L.begin(), R.length() - L.length(), '0');
    len = R.length();

    memset(dp, -1, sizeof(dp));
    cout << rec(0, 1, 1, 0, 0) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin >> t;
    while(t--) solve();
}