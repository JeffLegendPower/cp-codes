// https://codeforces.com/problemset/problem/1633/D

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    // dpb[i] cant be more than like 30
    ll dpb[1001];
    for (int i = 0; i <= 1000; i++) dpb[i] = 1e9;
    dpb[1] = 0;

    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= i; j++) {
            if (i + i/j > 1000) continue;
            dpb[i + i/j] = min(dpb[i + i/j], dpb[i]+1);
        }
    }
    
    int T; cin >> T;
    while (T--) {
        int N, k; cin >> N >> k;

        int b[N], c[N];
        for (int i = 0; i < N; i++) cin >> b[i];
        for (int i = 0; i < N; i++) cin >> c[i];

        ll dpk[k+1];
        dpk[0] = 0;

        k = min(k, 30*N);

        ll dp[k + 1];
        ll best = 0;
        for (int i = 0; i <= k; i++) dp[i] = 0;

        for (int i = 0; i < N; i++) {
            for (int j = k; j >= 0; j--) {
                if (j + dpb[b[i]] > k) continue;
                dp[j + dpb[b[i]]] = max(dp[j + dpb[b[i]]], dp[j] + c[i]);

                best = max(best, dp[j + dpb[b[i]]]);
            }
        }

        cout << best << endl;
    }
}