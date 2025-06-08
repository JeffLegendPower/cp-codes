// https://usaco.org/index.php?page=viewproblem2&cpid=492&lang=en

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

ll dist(pll &one, pll &two) {
    return abs(one.first - two.first) + abs(one.second - two.second);
}

int main() {
    // Comment out for interactive problems
    // ios::sync_with_stdio(false);
	// cin.tie(nullptr);
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);

    int N, K;
    cin >> N >> K;

    pll checkpoints[N];
    for (int i = 0; i < N; i++) cin >> checkpoints[i].first >> checkpoints[i].second;

    ll dp[N][K + 1];
    dp[0][0] = 0;
    for (int i = 1; i <= K; i++) dp[0][i] = 1e18;

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = 1e18;
            for (int k = 0; k <= j; k++) {
                if (i - k - 1 < 0) break;
                dp[i][j] = min(
                    dp[i][j], 
                    dp[i - k - 1][j - k] + dist(checkpoints[i], checkpoints[i - k - 1])
                );
            }
        }
    }

    ll least = 1e18;
    for (int i = 0; i <= K; i++) least = min(least, dp[N - 1][i]);

    cout << least;
}