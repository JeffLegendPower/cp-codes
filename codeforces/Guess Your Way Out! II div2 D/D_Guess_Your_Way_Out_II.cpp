// https://codeforces.com/problemset/problem/558/D

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


// convert range from [l, r] at level hi to range at bottom level
pll convert(ll l, ll r, int h, int hi) {
    int diff = h - hi;
    return {
        l<<(h-hi),
        (r<<diff)|((1ll<<diff) - 1)
    };
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int h, Q;
    cin >> h >> Q;
    
    ll l = 1ll<<(h-1), r = (1ll<<h)-1;

    vector<pll> qris;
    while (Q--) {
        int i, ans;
        ll L, R;
        cin >> i >> L >> R >> ans;

        pll rnge = convert(L, R, h, i);

        if (ans == 0) qris.push_back(rnge);
        else {
            l = max(l, rnge.first);
            r = min(r, rnge.second);
        }
    }

    sort(qris.begin(), qris.end());

    vector<pll> rngs;
    for (auto [li, ri] : qris) {
        if (ri < l) continue;
        if (li > r) continue;
        if (l > r) continue;

        if (li > l) rngs.push_back({l, li-1});

        l = ri + 1;
    }

    if (l <= r) rngs.push_back({l, r});

    ll len = 0;
    for (auto [li, ri] : rngs) len += ri-li+1;
    if (len == 0) cout << "Game cheated!";
    else if (len > 1) cout << "Data not sufficient!";
    else cout << rngs[0].first;
}