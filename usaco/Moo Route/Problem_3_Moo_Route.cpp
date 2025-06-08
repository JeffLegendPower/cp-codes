// https://usaco.org/index.php?page=viewproblem2&cpid=1283&lang=en

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

const ll MOD = 1e9 + 7;

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

ll fact[1000000 + 1], factinv[1000000 + 1];
ll ncr(ll n, ll r) {
    ll ans = (fact[n] * factinv[r]) % MOD;
    return (ans * factinv[n - r]) % MOD;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    fact[0] = 1;
    factinv[0] = 1;
    for (ll i = 1; i <= 1000000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        factinv[i] = modinv(fact[i]);
    }

    ll N; cin >> N;

    // each A[i] is a multiple of 2
    ll A[N]; for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i] /= 2;
    }

    // should actually be j=1e6 + 1 but sure for now
    // number of paths from x=i to the end to take if youre crossing BACKWARDS x=i-0.5 j times
    // assuming i is 1-indexed but its actually 0-indexed
    // dp[i][j]
    ll dp[N];
    for (int i = 0; i < N; i++) dp[i] = 0;

    // this is fixed as you cant go any more forward so from x=N-1 to x=N u can kinda just shimmy
    dp[N - 1] = 1;

    for (int i = N - 2; i >= 0; i--) {
        // cout << A[i] << endl;

        // for the transitions, we will look at how many times we can go back then forward the dp for x=i+1 when
        // it crosses back to right infront of x=i

        ll j = A[i + 1];
        // look at the # of ways we can cross it
        ll crosses = j - 1;

        // you nede to save an entry at the start
        if (A[i] - 1 <= crosses) dp[i] = (dp[i + 1] * ncr(crosses, A[i] - 1)) % MOD;

        else {
            // stars and bars
            ll k = A[i] - 1 - crosses;
            ll n = j + 1;
            dp[i] = (dp[i + 1] * ncr(k + n - 1, n - 1)) % MOD;
        }
    }

    cout << dp[0] << endl;
}