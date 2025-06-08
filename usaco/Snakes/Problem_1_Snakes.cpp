// https://usaco.org/index.php?page=viewproblem2&cpid=945

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

    setIO("snakes");

    int N, K;
    cin >> N >> K;

    ll snakes[N];
    for (int i = 0; i < N; i++) cin >> snakes[i];

    // min wasted from [0, i], currently using a net of size snakes[j], with k changes in net size
    // dp[i][j][k]

    // note that to calculate dp states i, we only need dp states i - 1
    // so to not MLE, we will only store dp state i % 2
    ll dp[2][N][K + 1];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k <= K; k++) {
                if (i == 0) dp[i][j][k] = 0;
                else dp[i][j][k] = 1e9;
            }
        }
    }

    // min wasted across all already using k changes
    // lets us do transitions in O(1) vs O(N)
    ll mindp[N + 1][K + 1];
    for (int i = 0; i <= N; i++) {
        for (int k = 0; k <= K; k++) mindp[i][k] = 1e9;
    }

    ll best = 1e9;
    for (int i = 0; i < N; i++) {
        best = 1e9;
        for (int k = K; k >= 0; k--) {
            for (int j = 0; j < N; j++) {
                if (snakes[j] < snakes[i]) {
                    dp[(i + 1)%2][j][k] = 1e9;
                    continue;
                }

                dp[(i + 1)%2][j][k] = dp[i%2][j][k];
                if (k > 0) {
                    dp[(i + 1)%2][j][k] = min(dp[(i + 1)%2][j][k], mindp[i][k - 1]);
                }

                dp[(i + 1)%2][j][k] += snakes[j] - snakes[i];

                mindp[i + 1][k] = min(mindp[i + 1][k], dp[(i + 1)%2][j][k]);

                best = min(best, dp[(i + 1)%2][j][k]);
            }
        }
    }

    cout << best;
}