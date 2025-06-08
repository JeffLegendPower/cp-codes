// https://usaco.org/index.php?page=viewproblem2&cpid=670

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

ll dist(pll one, pll two) {
    return (one.first - two.first) * (one.first - two.first) + (one.second - two.second) * (one.second - two.second);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("checklist");

    int H, G;
    cin >> H >> G;

    pll h[H], g[G];
    for (int i = 0; i < H; i++) cin >> h[i].first >> h[i].second;
    for (int i = 0; i < G; i++) cin >> g[i].first >> g[i].second;

    // cur holstein i, cur guernsey j, currently on holstein k=1, else k=0
    // already searched holstein i and searched guernsey j
    // dp[i][j][k]
    ll dp[H + 1][G + 1][2];
    for (int i = 0; i <= H; i++) {
        for (int j = 0; j <= G; j++) {
            dp[i][j][0] = 1e12;
            dp[i][j][1] = 1e12;
        }
    }
    dp[1][0][1] = 0;

    for (int i = 0; i <= H; i++) {
        for (int j = 0; j <= G; j++) {
            if (j == 1 && i >= 1) { // to first guernsey
                dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][1] + dist(g[j - 1], h[i - 1]));
            }

            if (i > 1) { // to next holstein
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][1] + dist(h[i - 1], h[i - 2]));
                dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][0] + dist(h[i - 1], g[j - 1]));
            } if (j > 1) { // to next guernsey
                dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][0] + dist(g[j - 1], g[j - 2]));
                dp[i][j][0] = min(dp[i][j][0], dp[i][j - 1][1] + dist(g[j - 1], h[i - 1]));
            }
        }
    }

    cout << dp[H][G][1];
}