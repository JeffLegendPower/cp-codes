// https://codeforces.com/contest/1882/problem/C

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
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        for (int i = 0; i < N; i++) cin >> a[i];

        ll dp[N];
        ll suff[N];
        dp[N - 1] = max(a[N - 1], 0ll);
        suff[N - 1] = dp[N - 1];
        for (int i = N - 2; i >= 0; i--) {
            dp[i] = 0;
            dp[i] = max(dp[i], a[i] + dp[i + 1]);

            if (i < N - 2) dp[i] = max(dp[i], suff[i + 2] + max(a[i], 0ll));
            suff[i] = max(dp[i], suff[i + 1]);

            // cout << dp[i] << endl;
        }

        cout << dp[0] << endl;
    }
}