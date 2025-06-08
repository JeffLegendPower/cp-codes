// https://codeforces.com/contest/1012/problem/C

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    ll a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    // index, num maxes (1 indexed)
    // dp[i][j] = cost
    ll dp[N][(N + 1) / 2];
    ll mins[(N + 1) / 2];
    for (int i = 0; i < (N + 1) / 2; i++) mins[i] = 1e10;


    for (int i = 0; i < N; i++) {
        ll singlecost = 0;
        if (i > 0) singlecost += max(a[i - 1] - a[i] + 1, 0ll);
        if (i < N - 1) singlecost += max(a[i + 1] - a[i] + 1, 0ll);
        dp[i][0] = singlecost;

        for (int j = 1; j < (N + 1) / 2; j++) {
            dp[i][j] = 1e10;
            if (i > 1) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 1] + singlecost - max(a[i - 1] - max(a[i], a[i - 2]) + 1, 0ll));
                dp[i][j] = min(dp[i][j], mins[j - 1] + singlecost);
            }
        }

        if (i < 2) continue;
        for (int j = 0; j < (N + 1) / 2; j++) {
            mins[j] = min(mins[j], dp[i - 2][j]);
        }
    }

    for (int j = 0; j < (N + 1) / 2; j++) {
        ll least = 1e10;
        for (int i = 0; i < N; i++) {
            least = min(least, dp[i][j]);
        }

        cout << least << " ";
    }
}