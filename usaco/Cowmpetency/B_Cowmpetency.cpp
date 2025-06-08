// https://vjudge.net/contest/663092#problem/B

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

ll MOD = 1e9 + 7;

ll binpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

const int MAXQ = 100, MAXC = 1e4;
ll dp[MAXQ][MAXC + 1];
ll dpsumm[MAXQ][MAXC + 1];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll N, Q, C;
    cin >> N >> Q >> C;

    pll h[Q];
    for (int i = 0; i < Q; i++) {
        cin >> h[i].first >> h[i].second;
    }
    sort(h, h + Q);

    for (int i = 0; i < Q; i++) {
        auto [ai, hi] = h[i];
        ll last = (i == 0 ? 0 : h[i - 1].second);
        for (int c = 2; c <= C; c++) {
            // dpsumm[i][c] = 0;
            // if (c > 2) dpsumm[i][c] = (dpsumm[i][c] + dpsumm[i - 1][c]) % MOD;

            // dp[i][c] = binpow(c - 1, hi - last - 1);
            // if (i > 0) dp[i][c] = (dp[i][c] * dpsumm[i - 1][c - 1]) % MOD;
            // dpsumm[i][c] = (dpsumm[i][c] + dp[i][c]) % MOD;

            // cout << i << " " << c << " " << dp[i][c] << endl;

            dp
        }
    }

    ll total = 0;
    for (int i = 2; i <= C; i++) {
        total = (total + dp[Q - 1][i]) % MOD;
    }

    if (C == 1) total = 1;

    total = (total * binpow(C, N - h[Q - 1])) % MOD;
    cout << total;
}