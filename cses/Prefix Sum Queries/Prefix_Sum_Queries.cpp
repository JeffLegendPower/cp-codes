// https://cses.fi/problemset/task/2166

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


struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 2e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

int h;
ll d[2 * Nmax];

void apply(int p, ll val) {
    t[p] += val;
    if (p < N) d[p] += val;
}

void build(int p) {
    while (p > 1) {
        p >>= 1;
        t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
    }
}

void push(int p) {
    for (int s = h; s > 0; s--) {
        int i = p >> s;
        if (d[i] != 0) {
            apply(i<<1, d[i]);
            apply(i<<1|1, d[i]);
            d[i] = 0;
        }
    }
}

void modify(int l, int r, ll val) {
    l += N, r += N;
    int l0 = l, r0 = r;

    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, val);
        if (r&1) apply(--r, val);
    }

    build(l0);
    build(r0 - 1);
}

ll query(int l, int r) {  // on interval [l, r)
    l += N, r += N;
    push(l);
    push(r - 1);

    ll res = -2e12;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) res = max(res, t[l++]);
        if (r&1) res = max(res, t[--r]);
    }

    return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int Q;
    cin >> N >> Q;
    h = sizeof(int) * 8 - __builtin_clz(N);

    ll x[N];

    for (int i = 0; i < N; i++) {
        cin >> x[i];
        t[N + i] = x[i];
        if (i > 0) t[N + i] += t[N + i - 1];
        // cout << t[N + i] << endl;
    }

    for (int i = 0; i < N; i++) build(i + N);

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int k;
            ll u;
            cin >> k >> u;

            ll old = x[k - 1];
            x[k - 1] = u;

            ll diff = u - old;

            modify(k - 1, N, diff);
        } else if (t == 2) {
            int a, b;
            cin >> a >> b;

            ll ans = query(a - 1, b);
            if (a > 1) ans -= query(a - 2, a - 1);

            cout << max(0ll, ans) << endl;
        }
    }
}