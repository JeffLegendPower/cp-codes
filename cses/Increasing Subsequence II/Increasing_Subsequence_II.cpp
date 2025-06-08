// https://cses.fi/problemset/task/1748

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
    bool operator() (const ll& a, const ll& b) const {
        return a < b;
    }
};

typedef tree<ll, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const ll MOD = 1e9 + 7;

// Segtree start
const int Nmax = 2e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

ll oper(ll a, ll b) {
    return (a + b) % MOD;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, ll value) {  // set value at position p
  for (t[p] = (t[p += N] + value) % MOD; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 0;
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

    cin >> N;

    ll a[N];
    ordered_set oset;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        oset.insert(a[i]);
    }

    ll dp[N];
    ll total = 0;
    for (int i = 0; i < N; i++) {
        int idx = oset.order_of_key(a[i]);

        dp[i] = query(0, idx) + 1;

        total = (total + dp[i]) % MOD;
        modify(idx, dp[i]);
    }

    cout << endl;

    cout << total;
}