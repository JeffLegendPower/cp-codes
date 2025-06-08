// https://codeforces.com/contest/2057/problem/D

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
class SegmentTree {
private:
    static const int N = 2e5; // Maximum array size
    vector<ll> t;  // Segment tree array
    vector<ll> d;               // Lazy propagation array
    int n;                   // Size of the array
    int h;                   // Height of the segment tree

    void apply(int p, int value) {
        t[p] += value;
        if (p < n) d[p] += value;
    }

    void build(int p) {
        while (p > 1) {
            p >>= 1;
            t[p] = max(t[p << 1], t[p << 1 | 1]) + d[p];
        }
    }

    void push(int p) {
        for (int s = h; s > 0; --s) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i << 1, d[i]);
                apply(i << 1 | 1, d[i]);
                d[i] = 0;
            }
        }
    }

public:
    SegmentTree(int size) : n(size) {
        t.resize(2 * n, 0);
        d.resize(n, 0);
        h = sizeof(int) * 8 - __builtin_clz(n);
    }

    void inc(int l, int r, int value) {
        l += n;
        r += n;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, value);
            if (r & 1) apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }

    ll query(int l, int r) {
        l += n;
        r += n;
        push(l);
        push(r - 1);
        ll res = 0;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(t[--r], res);
        }
        return res;
    }
};

class Segtree {
private:
    vector<ll> t;  // Segment tree array
    int n;          // Size of the array

public:
    Segtree(int size) : n(size) {
        t.resize(2 * n, 0);
    }

    void build() {
        for (int i = n - 1; i > 0; --i) {
            t[i] = min(t[i << 1], t[i << 1 | 1]);
        }
    }

    void modify(int p, ll value) {
        for (t[p += n] = value; p > 1; p >>= 1) {
            t[p >> 1] = min(t[p], t[p ^ 1]);
        }
    }

    ll query(int l, int r) {
        ll res = 1e18;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }
};
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;

        SegmentTree ans1(N), ans2(N);
        Segtree left(N), right(N);

        ll a[N]; for (int i = 0; i < N; i++) cin >> a[i];

        for (int i = 0; i < N; i++) {
            ans1.inc(i,i+1, a[i] + N - i);
            ans2.inc(i,i+1, a[i] + i);
            
            left.modify(i, a[i] + N - i);
            right.modify(i, a[i] + i);

            ans1.inc(i,i+1, -left.query(0, i+1));
        }

        for (int i = 0; i < N; i++) {
            ans2.inc(i,i+1, -right.query(i, N));
        }

        cout << max(ans1.query(0, N), ans2.query(0, N)) << endl;

        while (Q--) {
            int p;
            ll x;
            cin >> p >> x;
            p--;

            int low = p, high = N-1;
            int best = p;
            while (low <= high) {
                int mid = low+(high-low)/2;

                ll res = 
            }

            left.modify(p, x )
        }
    }
}