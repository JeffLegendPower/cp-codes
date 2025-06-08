// https://codeforces.com/contest/1221/problem/D

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

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll a[N], b[N];
        for (int i = 0; i < N; i++) cin >> a[i] >> b[i];

        // idx, num increases
        ll dp[N][3];
        dp[0][0] = 0;
        dp[0][1] = b[0];
        dp[0][2] = 2 * b[0];
        for (int i = 1; i < N; i++) {
            ll minlast = min(dp[i - 1][0], min(dp[i - 1][1], dp[i - 1][2]));
            dp[i][0] = minlast;
            dp[i][1] = b[i] + minlast;
            dp[i][2] = 2 * b[i] + minlast;

            if (a[i] == a[i - 1]) {
                dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]);
                dp[i][1] = b[i] + min(dp[i - 1][0], dp[i - 1][2]);
                dp[i][2] = 2 * b[i] + min(dp[i - 1][0], dp[i - 1][1]);
            } else if (a[i] - 1 == a[i - 1]) {
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][2]);
                dp[i][1] = b[i] + min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][2] = 2 * b[i] + minlast;
            } else if (a[i] - 2 == a[i - 1]) {
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][1] = b[i] + minlast;
                dp[i][2] = 2 * b[i] + minlast;
            } else if (a[i] + 1 == a[i - 1]) {
                dp[i][0] = minlast;
                dp[i][1] = b[i] + min(dp[i - 1][1], dp[i - 1][2]);
                dp[i][2] = 2 * b[i] + min(dp[i - 1][0], dp[i - 1][2]);
            } else if (a[i] + 2 == a[i - 1]) {
                dp[i][0] = minlast;
                dp[i][1] = b[i] + minlast;
                dp[i][2] = 2 * b[i] + min(dp[i - 1][1], dp[i - 1][2]);
            }
        }

        cout << min(dp[N - 1][0], min(dp[N - 1][1], dp[N - 1][2])) << endl;
    }
}