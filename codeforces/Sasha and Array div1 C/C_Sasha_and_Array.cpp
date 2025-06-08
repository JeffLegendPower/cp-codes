// https://codeforces.com/problemset/problem/718/C

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

#define matrix array<array<ll, 2>, 2>

ll MOD = 1e9 + 7;

matrix multi(matrix one, matrix two) {
    matrix ans;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ans[i][j] = 0;
            for (int k = 0; k < 2; k++) ans[i][j] = (ans[i][j] + one[i][k] * two[k][j]) % MOD;
        }
    }
    return ans;
}

map<ll, matrix> precomp;
matrix binpow(matrix M, ll b) {
    matrix res = {{{1, 0}, {0, 1}}};

    while (b > 0) {
        if (b & 1)
            res = multi(res, M);

        M = multi(M, M);

        b >>= 1;
    }
    return res;
}

template <class T, class K>
class LazySegtree {
private:
    int N;  // array size
    int h;
    vector<T> t;
    vector<K> d;

    matrix identity = {{{1, 0}, {0, 1}}};

    T combine(T a, T b) {
        return a + b;
    }

    // k is the length of the segment
    T calc(T a, T b, K d, int k) {
        T ans = {a[0] + b[0], a[1] + b[1]};

        ans = {(d[0][0] * ans[0] + d[0][1] * ans[1]) % MOD, (d[1][0] * ans[0] + d[1][1] * ans[1]) % MOD};

        return ans;
    }

    // Update d[p]
    // k is the length of segment
    void apply(int p, K value, int k) {
        // Update t[p] as if it was already affected by d[p]

        t[p] = {
            (value[0][0] * t[p][0] + value[0][1] * t[p][1]) % MOD, 
            (value[1][0] * t[p][0] + value[1][1] * t[p][1]) % MOD
        };
        
        if (p < N) d[p] = multi(value, d[p]);
    }

public:
    LazySegtree(int size) : N(size), h(sizeof(int) * 8 - __builtin_clz(N)), t(2 * size, T()), d(size) {
        for (int i = 0; i < N; i++) {
            t[N+i] = {0, 1};
            d[i] = {{{1, 0}, {0, 1}}};
        }
        build(0, N);
    }

    void build(int l, int r) {
        int k = 2;
        for (l += N, r += N-1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i) t[i] = calc(t[i<<1], t[i<<1|1], d[i], k);
        }
    }

    void push(int l, int r) {
        int s = h, k = 1 << (h-1);
        for (l += N, r += N-1; s > 0; --s, k >>= 1) for (int i = l >> s; i <= r >> s; ++i) if (d[i] != identity) {
            apply(i<<1, d[i], k);
            apply(i<<1|1, d[i], k);
            d[i] = {{{1, 0}, {0, 1}}};
        }
    }

    void modify(int l, int r, K value) {
        // if (value == 0) return;
        push(l, l + 1);
        push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l&1) apply(l++, value, k);
            if (r&1) apply(--r, value, k);
        }
        build(l0, l0 + 1);
        build(r0 - 1, r0);
    }

    T query(int l, int r) {
        push(l, l + 1);
        push(r - 1, r);
        T res = {0, 0};
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = calc(res, t[l++], identity, -1);
            if (r&1) res = calc(res, t[--r], identity, -1);
        }
        return res;
    }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    matrix fibnext = {{{1, 1}, {1, 0}}};

    ll a[N];
    LazySegtree<array<ll, 2>, matrix> segtree(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        segtree.modify(i, i+1, binpow(fibnext, a[i]));
    }

    while (M--) {
        int tp; cin >> tp;
        if (tp == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            segtree.modify(l-1, r, binpow(fibnext, x));
        } else {
            int l, r;
            cin >> l >> r;
            cout << segtree.query(l-1, r)[0] << endl;
        }
    }
}