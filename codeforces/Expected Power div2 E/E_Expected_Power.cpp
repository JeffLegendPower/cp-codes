// https://codeforces.com/problemset/problem/2020/E

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

ll binpow(ll a, ll b, ll MOD) {
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
ll modinv(ll x, ll MOD) {
    return binpow(x, MOD - 2, MOD);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll MOD = 1e9 + 7;

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll dp[1<<10][2];
        for (int i = 0; i < 1<<10; i++) {
            dp[i][0] = 0;
            dp[i][1] = 0;
        }
        dp[0][0] = 1;

        pll ap[N];
        for (int i = 0; i < N; i++) cin >> ap[i].first;
        for (int i = 0; i < N; i++) cin >> ap[i].second;

        ll total = 1;
        for (int i = 0; i < N; i++) {
            auto [a, p] = ap[i];
            ll p2 = 1e4 - p;
            int i2 = i&1;

            total = (total * 10000) % MOD;

            for (int j = 0; j < 1<<10; j++) dp[j][i2^1] = 0;
            for (int j = 0; j < 1<<10; j++) {
                dp[j][i2^1] += (dp[j][i2] * p2) % MOD;
                dp[j^a][i2^1] += (dp[j][i2] * p) % MOD;
            }
        }

        ll expected = 0;
        for (int i = 0; i < 1<<10; i++) {
            ll num = (i * i) % MOD;
            ll diff = (dp[i][N&1] * num) % MOD;
            expected = (expected + diff) % MOD;
        }

        expected = (expected * modinv(total, MOD)) % MOD;
        cout << expected << endl;
    }
}