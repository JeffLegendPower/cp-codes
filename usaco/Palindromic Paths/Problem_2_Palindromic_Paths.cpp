// https://usaco.org/index.php?page=viewproblem2&cpid=553

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define plli pair<ll, int>
#define pll pair<ll, ll>
#define pii pair<int, int>
// Usage: FOR(i, 0, N) {...}
#define FOR(i, start, end) for(int i = start; i < end; i++)

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 1e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("palpath");

    int N;
    cin >> N;

    ll MOD = 1e9 + 7;

    char grid[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> grid[i][j];
    }

    ll dp[2][N][N]; // this will use too much memory so make sure to fix this

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) dp[i][j][k] = 0;
        }
    }

    if (grid[0][0] == grid[N - 1][N - 1]) dp[0][0][0] = 1;

    for (int l = 1; l < N; l++) {
        int l2 = l&1;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) dp[l2][i][j] = 0;
        }

        for (int i = 0; i < N; i++) {
            if (i > l) break;

            for (int j = 0; j < N; j++) {
                if (j > l) break;

                if (grid[i][l - i] != grid[N - 1 - j][N - 1 - l + j]) continue;

                dp[l2][i][j] = (dp[l2][i][j] + dp[l2^1][i][j]) % MOD;
                if (i > 0) dp[l2][i][j] = (dp[l2][i][j] + dp[l2^1][i - 1][j]) % MOD;
                if (j > 0) dp[l2][i][j] = (dp[l2][i][j] + dp[l2^1][i][j - 1]) % MOD;
                if (i > 0 && j > 0) dp[l2][i][j] = (dp[l2][i][j] + dp[l2^1][i - 1][j - 1]) % MOD;
            }
        }
    }

    ll total = 0;
    for (int i = 0; i < N; i++) total = (total + dp[(N - 1)&1][i][N - 1 - i]) % MOD;
    
    cout << total;
}