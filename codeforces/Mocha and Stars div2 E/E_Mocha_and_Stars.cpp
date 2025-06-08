// https://codeforces.com/contest/1559/problem/E

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

const int MOBIUSMAX = 1e5 + 1;
ll mobius[MOBIUSMAX];

void calcmobius() {
    mobius[1] = -1;
    mobius[0] = 0;

    for (int i = 1; i < MOBIUSMAX; i++) {
        if (mobius[i]) {
            mobius[i] = -mobius[i];
            for (int j = 2 * i; j < MOBIUSMAX; j += i) { mobius[j] += mobius[i]; }
        }
    }
}

ll MOD = 998244353;

ll solve(int N, vector<int> &lows, vector<int> &highs, ll bound) {
    vector<ll> ans(bound+1, 0);
    ans[0] = 1;

    for (int i = 0; i < N; i++) {
        vector<ll> pre(bound+2, 0);
        for (int j = 1; j < bound+2; j++) pre[j] = (pre[j-1] + ans[j-1]) % MOD;

        vector<ll> ans2(bound+1, 0);
        for (int j = lows[i]; j < bound+1; j++) {
            ans2[j] += pre[j - lows[i] + 1] - pre[max(0, j - highs[i])];
            ans2[j] %= MOD;
        }

        for (int j = 0; j < bound+1; j++) ans[j] = ans2[j];
    }

    ll total = 0;
    for (int i = 0; i < bound+1; i++) total = (total + ans[i]) % MOD;
    
    return total;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<ll> lows(N), highs(N);
    for (int i = 0; i < N; i++) cin >> lows[i] >> highs[i];

    calcmobius();

    ll total = 0;

    for (int d = 1; d <= M; d++) {
        vector<int> lowsd(N), highsd(N);
        for (int i = 0; i < N; i++) {
            lowsd[i] = (lows[i] + d - 1) / d;
            highsd[i] = highs[i] / d;
        }

        ll ans = solve(N, lowsd, highsd, M / d);
        total = (total + mobius[d] * ans) % MOD;
    }

    cout << total;
}