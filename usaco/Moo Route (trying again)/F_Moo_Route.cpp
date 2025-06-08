// https://usaco.org/index.php?page=viewproblem2&cpid=1283

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

ll fact[1000001];
ll ncr(ll n, ll r) {
    ll res = (fact[n] * modinv(fact[r])) % MOD;
    return (res * modinv(fact[n-r])) % MOD;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    fact[0] = 1;
    for (ll i = 1; i <= 1000000; i++) fact[i] = (fact[i-1]*i)%MOD;

    int N; cin >> N;
    ll A[N];
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i] /= 2;
    }

    // i is 0-indexed for this description
    // dp[i] is num ways to start and end at i ignoring left and going right
    ll dp[N];
    dp[N-1] = 1;

    for (int i = N-2; i >= 0; i--) {
    // need to always greedily right if possible to minimize # turns
    // so if possible we dont want to just go to i+1 and then back if we can go to i+2 and so on

        if (A[i] > A[i+1]) {
            // we cant always go to i+2... so we will go as many times as possible and account for num ways it can be arranged
            dp[i] = (dp[i+1] * ncr(A[i], A[i+1])) % MOD;
        } else {
            // we can always go to i+2 so we will... but we have "extra" moves which we will see how many ways they can be arranged
            dp[i] = (dp[i+1] * ncr(A[i] + A[i+1] - A[i] - 1, A[i+1] - A[i])) % MOD;
        }
    }

    cout << dp[0];
}