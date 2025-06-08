// https://codeforces.com/contest/2024/problem/D

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
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 5e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
}

void modify(int p, ll value) {  // set value at position p
    p += N;
  for (t[p] = min(t[p], value); p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
}

ll query(int l, int r) {  // sum on interval [l, r)
  ll res = 1e18;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(res, t[--r]);
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
        cin >> N;

        ll a[N], b[N];
        ll pres[N + 1];
        pres[0] = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            pres[i + 1] = pres[i] + a[i];
            t[N + i] = 1e18;
        } for (int i = 0; i < N; i++) cin >> b[i];

        build();
        modify(0, 0);

        // min skips to get to idx i
        ll dp[N];
        dp[0] = 0;
        for (int i = 0; i < N; i++) {
            dp[i] = query(i, N);
            int bi = b[i];
            ll cost = dp[i] + a[i];

            if ((bi - 1) > i) modify(bi - 1, cost);
        }

        ll best = 0;
        for (int i = 0; i < N; i++) {
            best = max(best, pres[i + 1] - query(i, N));
            // cout << pres[i + 1] << " " << query(i, N) << " " << i << endl;
        }

        cout << best << endl;
    }
}