// https://usaco.org/index.php?page=viewproblem2&cpid=578

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


template <class T, class K>
class LazySegtree {
private:
    int N;  // array size
    int h;
    vector<T> t;
    vector<K> d;

    T combine(T a, T b) {
        return a + b;
    }

    // k is the length of the segment
    T calc(T a, T b, K d, int k) {
        T res = {a.first + b.first + d*k, min(a.second, b.second) + d};
        return res;
    }

    // Update d[p]
    // k is the length of segment
    void apply(int p, K value, int k) {
        // Update t[p] as if it was already affected by d[p]
        t[p].first += value*k;
        t[p].second += value;

        if (p < N) d[p] += value;
    }

public:
    LazySegtree(int size) : N(size), h(sizeof(int) * 8 - __builtin_clz(N)), t(2 * size, T()), d(size, K()) {}

    void build(int l, int r) {
        int k = 2;
        for (l += N, r += N-1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i) t[i] = calc(t[i<<1], t[i<<1|1], d[i], k);
        }
    }

    void push(int l, int r) {
        int s = h, k = 1 << (h-1);
        for (l += N, r += N-1; s > 0; --s, k >>= 1) for (int i = l >> s; i <= r >> s; ++i) if (d[i] != 0) {
            apply(i<<1, d[i], k);
            apply(i<<1|1, d[i], k);
            d[i] = 0;
        }
    }

    void modify(int l, int r, K value) {
        if (value == 0) return;
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
        T res = {0, 1e18};
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = calc(res, t[l++], 0, -1);
            if (r&1) res = calc(res, t[--r], 0, -1);
        }
        return res;
    }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("haybales");

    int N, Q;
    cin >> N >> Q;

    LazySegtree<pll, ll> bales(N);
    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        bales.modify(i, i+1, x);
    }

    while (Q--) {
        char c; cin >> c;

        if (c == 'M') {
            int A, B; cin >> A >> B;
            cout << bales.query(A-1, B).second;
            if (Q>0) cout << endl;
        } if (c == 'P') {
            int A, B; ll C;
            cin >> A >> B >> C;
            bales.modify(A-1, B, C);
        } if (c == 'S') {
            int A, B; cin >> A >> B;
            cout << bales.query(A-1, B).first;
            if (Q>0) cout << endl;
        }
    }
}