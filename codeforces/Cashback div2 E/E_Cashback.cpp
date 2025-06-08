// https://codeforces.com/contest/940/problem/E

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

    int N, c;
    cin >> N >> c;

    ll a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    ll dp[N + 1];
    dp[0] = 0;
    for (int i = 0; i < c - 1; i++) dp[i + 1] = dp[i] + a[i];

    ordered_multiset window;
    ll windowsum = 0;
    for (int i = 0; i < c; i++) {
        window.insert({a[i], i});
        windowsum += a[i];
    }

    for (int i = c - 1; i < N; i++) {
        dp[i + 1] = dp[i] + a[i];
        dp[i + 1] = min(dp[i + 1], dp[i - c + 1] + windowsum - window.find_by_order(0)->first);

        if (i < N - 1) {
            window.erase({a[i - c + 1], i - c + 1});
            window.insert({a[i + 1], i + 1});

            windowsum -= a[i - c + 1];
            windowsum += a[i + 1];
        }
    }

    cout << dp[N] << endl;
}