// https://codeforces.com/problemset/problem/1946/E

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
} ll modinv(ll x) {
    return binpow(x, MOD - 2);
}

ll fact[200001], factinv[200001];

ll ncr(int n, int r) {
    ll res = (fact[n] * factinv[r]) % MOD;
    return (res * factinv[n - r]) % MOD;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    fact[0] = 1, factinv[0] = 1;
    for (ll i = 1; i < 200000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        factinv[i] = modinv(fact[i]);
    }

    int T; cin >> T;

    while (T--) {
        int N, m1, m2; cin >> N >> m1 >> m2;

        int p1[m1], p2[m2];
        for (int i = 0; i < m1; i++) cin >> p1[i];
        for (int i = 0; i < m2; i++) cin >> p2[i];

        if (p1[m1 - 1] != p2[0] || p1[0] > 1 || p2[m2 - 1] < N) {
            cout << 0 << endl;
            continue;
        }

        ll ways = ncr(N - 1, p2[0] - 1);

        for (int i = m1 - 2; i >= 0; i--) {
            ways = (ways * ncr(p1[i + 1] - 2, p1[i] - 1)) % MOD;
            ways = (ways * fact[p1[i + 1] - p1[i] - 1]) % MOD;
        } 
        for (int i = 1; i < m2; i++) {
            ways = (ways * ncr(N - p2[i - 1] - 1, N - p2[i])) % MOD;
            ways = (ways * fact[p2[i] - p2[i - 1] - 1]) % MOD;
        }

        cout << ways << endl;
    }
}