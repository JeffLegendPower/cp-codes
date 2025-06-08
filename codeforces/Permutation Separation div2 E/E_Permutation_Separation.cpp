// https://codeforces.com/contest/1295/problem/E

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
const int N = 2e5;  // limit for array size
int n;  // array size
ll t[2 * N];

int h;
ll d[N];

void apply(int p, ll value) {
    t[p] += value;
    if (p < n) d[p] += value;
}

void build(int p) {
    while (p > 1) p >>= 1, t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
}

void push(int p) {
    for (int s = h; s > 0; --s) {
        int i = p >> s;
        if (d[i] != 0) {
            apply(i<<1, d[i]);
            apply(i<<1|1, d[i]);
            d[i] = 0;
        }
    }
}

void inc(int l, int r, ll value) {
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
    }
    build(l0);
    build(r0 - 1);
}

ll query(int l, int r) {
    l += n, r += n;
    push(l);
    push(r - 1);
    ll res = 1e18;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = min(res, t[l++]);
        if (r&1) res = min(t[--r], res);
    }
    return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;
    n = N;
    h = sizeof(int) * 8 - __builtin_clz(n);

    int p[N], idxs[N+1];
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        idxs[p[i]] = i;
    }

    ll a[N], pre[N + 1];
    pre[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        pre[i+1] = pre[i] + a[i];

        inc(i, i+1, pre[i+1]);
    }

    ll ans = query(0, N-1);
    for (int i = 1; i <= N; i++) {
        int idx = idxs[i];
        inc(0, idx, a[idx]);
        inc(idx, N, -a[idx]);

        ans = min(ans, query(0, N-1));
    }
    cout << ans;
}