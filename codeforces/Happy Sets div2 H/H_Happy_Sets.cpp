// https://codeforces.com/problemset/problem/1866/H

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

ll binpow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
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

    ll N, K;
    cin >> N >> K;

    ll MOD = 1e9 + 7;

    vector<ll> fact(N + 1, 1);
    // vector<ll> pow2(K + 1, 1);
    for (ll i = 1; i <= N; i++) fact[i] = (fact[i - 1] * i) % MOD;
    // for (ll i = 1; i <= N; i++) pow2[i] = (pow2[i - 1] * 2) % MOD;

    vector<ll> dp(K + 1, 1);

    ll total = 1;
    dp[0] = 0;
    total += (K * N) % MOD;

    for (int i = 2; i <= N; i++) {
        ll summ = 0;
        ll last = 0;
        for (int j = 1; j <= K; j++) {
            summ = (summ * 2) % MOD;
            summ = (summ + last) % MOD;
            ll tmp = dp[j];
            dp[j] = summ;

            summ = (summ + tmp) % MOD;
            last = tmp;

            ll addd = (fact[N] * modinv(fact[N - 2], MOD)) % MOD;
            addd = (addd * dp[j]) % MOD;
            total = (total + addd) % MOD;
        }
    }

    cout << total;
}