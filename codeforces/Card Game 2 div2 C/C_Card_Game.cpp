// https://codeforces.com/problemset/problem/1739/C

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

ll MOD = 998244353;

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

ll fact[61];

ll ncr(ll n, ll k) {
    ll ans = fact[n];
    ans = (ans * modinv(fact[k])) % MOD;
    ans = (ans * modinv(fact[n - k])) % MOD;
    return ans;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    fact[0] = 1;
    for (ll i = 1; i <= 60; i++) fact[i] = (fact[i - 1] * i) % MOD;

    int T; cin >> T; while (T--) {
        int n; cin >> n;

        ll alex = 0;
        ll boris = 0;

        // alex has largest
        // ncr(N - 1, N / 2 - 1)
        // alex has 3rd largest then needs also 4th and alex has 2nd boris has 1st
        // alex has 5th largest then also needs 3rd largest and 2nd boris has 1st and 4th

        int turn = 0;
        ll numalex = 0, numboris = 0;
        for (int most = n; most > 0; most--) {
            if (turn == 0 || turn == 3) {
                alex = (alex + ncr(n - numalex - numboris - 1, n/2 - numalex - 1)) % MOD;
                numboris++;
            } else {
                boris = (boris + ncr(n - numalex - numboris - 1, n/2 - numboris - 1)) % MOD;
                numalex++;
            }

            turn = (turn + 1) % 4;
        }

        cout << alex << " " << boris << " " << 1 << endl;
    }
}