// https://codeforces.com/problemset/problem/1832/E

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

ll dp[10000001][6];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
    ll MOD = 998244353;

    int N;
    ll a1, x, y, m, k;
    cin >> N >> a1 >> x >> y >> m >> k;

    // we can solve using dp as
    // b[i] = sum from j=1 to i of (((i - j + 1) choose k) * a[j])
    // which is equal to sum from j=1 to i of (((i - j) choose k) * a[j])   +   sum from j=1 to i of (((i - j) choose (k - 1)) * a[j])
    // which is equal to b[i - 1] + (b[i - 1] if k = k - 1)
    // so we solve using dp for all b and k

    ll a[N];
    a[0] = a1;
    for (int i = 1; i < N; i++) a[i] = (a[i - 1] * x + y) % m;

    for (int i = 0; i <= k; i++) dp[0][i] = 0;
    for (int i = 0; i < N; i++) {
        dp[i + 1][0] = (dp[i][0] + a[i]) % MOD;
    }

    ll ans = 0;
    for (ll i = 1; i <= N; i++) {
        dp[i][1] = (dp[i - 1][1] + dp[i][0]) % MOD;
        for (int j = 2; j <= k; j++) {
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
        }

        ans ^= dp[i][k] * i;
    }

    cout << ans;
}