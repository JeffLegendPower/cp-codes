// Problem link here:

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

constexpr ll MOD = 1e9 + 7;

ll binpow(ll a, ll b, ll MOD) {
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
    return binpow(x, MOD - 2, MOD);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, L, K;
        cin >> N >> L >> K;

        // dp[i][j]: expected number of matches for the jth person if starting at lock i and the 1st person
        // remember at lock i (0 indexed), there are L-i keys left
        ll dp[L][N];
        for (int j = 0; j < N; j++) {
            dp[L-1][j] = 0;
        }
        dp[L-1][0] = 1;

        for (int i = L-2; i >= 0; i--) {
            ll locks = L-i;
            ll denom = modinv(locks);
            for (int j = 0; j < N; j++) dp[i][j] = 0;

            for (int j = 0; j < N; j++) {
                ll numer = (locks + N - 1 - j) / N;
                ll frac = (numer * denom) % MOD;
                
                dp[i][j] = (dp[i][j] + frac) % MOD;

                for (int k2 = 0; k2 < N; k2++) {
                    int k = (j+k2+1)%N;
                    dp[i][k] = (dp[i][k] + frac*dp[i+1][k2]) % MOD;
                }
            }
        }

        for (int j = 0; j < N; j++) cout << dp[0][j] << " ";
        cout << endl;
    }
}