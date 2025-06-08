// https://codeforces.com/contest/2030/problem/E

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

ll MOD = 998244353;

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
} ll modinv(ll a) {
    return binpow(a, MOD - 2);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll fact[200000 + 1];
    ll factinv[200000 + 1];
    fact[0] = 1;
    factinv[0] = 1;

    for (ll i = 1; i <= 200000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        factinv[i] = modinv(fact[i]);
    }

    int T;
    cin >> T;
    while (T--) {
        ll N; cin >> N;

        vector<ll> cnts(N, 0);
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            cnts[a]++;
        }

        ll num = N;
        ll total = 0;

        // for how many subsets does there exist i open multisets
        // dp[idx&1][i]
        vector<vector<ll>> dp(2, vector<ll>(N + 1, 0));
        for (int i = 0; i < N; i++) {
            num -= cnts[i];

            ll ncr[cnts[i] + 1];
            for (int j = 0; j <= cnts[i]; j++) {
                ncr[j] = (fact[cnts[i]] * factinv[j]) % MOD;
                ncr[j] = (ncr[j] * factinv[cnts[i] - j]) % MOD;
            }

            int i2 = i^1;

            ll suff = 0;
            ll ncrsuff = 0;
            for (ll j = N/max(1, i); j >= 0; j--) dp[i&1][j] = 0;
            for (ll j = N/max(1, i); j > cnts[i]; j--) suff = (suff + dp[i2&1][j]) % MOD;

            for (ll j = cnts[i]; j >= 1; j--) {
                if (i == 0) {
                    dp[i&1][j] = ncr[j];
                    ll addd = (dp[i&1][j] * j) % MOD;
                    addd = (addd * binpow(2, num)) % MOD;
                    total = (total + addd) % MOD;
                    continue;
                }

                suff = (suff + dp[i2&1][j]) % MOD;
                // cout << suff << " " << j << " " << ncrsuff << endl;
                dp[i&1][j] = (ncr[j] * suff) % MOD;
                dp[i&1][j] = (dp[i&1][j] + ((dp[i2&1][j] * ncrsuff) % MOD)) % MOD;
                ncrsuff = (ncrsuff + ncr[j]) % MOD;

                ll addd = (dp[i&1][j] * j) % MOD;
                addd = (addd * binpow(2, num)) % MOD;
                total = (total + addd) % MOD;
            }
        }

        cout << total << endl;
    }
}