// https://codeforces.com/contest/1811/problem/G2

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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
ll fact[5001];

ll binpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll modinv(ll x) {
    return binpow(x, MOD - 2);
}

ll ncr(ll n, ll r) {
    ll ans = (fact[n] * modinv(fact[r])) % MOD;
    return (ans * modinv(fact[n - r])) % MOD;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    fact[0] = 1;
    for (ll i = 1; i <= 5000; i++) fact[i] = (fact[i - 1] * i) % MOD;

    int T; cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;

        int c[N]; for (int i = 0; i < N; i++) cin >> c[i];

        if (K == 1) {
            cout << 1 << endl;
            continue;
        }

        ll nck[N+1];
        for (int i = 0; i <= N; i++) nck[i] = ncr(i, K - 2);

        pll dp[N], dpsum[N + 1];
        dpsum[0] = {1, 0};
        for (int i = 0; i < N; i++) {
            dp[i] = {0, 0};
            dpsum[i+1] = {1, 0};
        }

        vector<vector<int>> idxs(N + 1);
        for (int i = 0; i < N; i++) {
            idxs[c[i]].push_back(i);
            for (int j = 0; j + K <= idxs[c[i]].size(); j++) {
                ll between = idxs[c[i]].size() - j - 2;
                ll choose = nck[between];

                pll ans = { (dpsum[idxs[c[i]][j]].first * choose) % MOD, dpsum[idxs[c[i]][j]].second + K };

                if (ans.second > dp[i].second) {
                    dp[i] = ans;
                } else if (ans.second == dp[i].second) {
                    dp[i].first += ans.first;
                    dp[i].first %= MOD;
                }
            }

            for (int j = i+1; j <= N; j++) {
                if (dp[i].second > dpsum[j].second) {
                    dpsum[j] = dp[i];
                } else if (dp[i].second == dpsum[j].second) {
                    dpsum[j].first += dp[i].first;
                    dpsum[j].first %= MOD;
                }
            }
        }

        cout << dpsum[N].first << endl;
    }
}