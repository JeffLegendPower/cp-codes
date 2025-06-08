// https://codeforces.com/problemset/problem/2089/B2

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


class Segtree {
private:
    int N;  // array size

    struct entry {
        ll sumA, sumB;
        ll extraA, extraB;
    };

    vector<entry> t;

    entry combine(entry a, entry b) {
        entry res;
        res.sumA = a.sumA + b.sumA;
        res.sumB = a.sumB + b.sumB;
        res.extraA = max(a.extraA - b.extraB, 0ll) + b.extraA;
        res.extraB = a.extraB + max(b.extraB - a.extraA, 0ll);
        return res;
    }

public:
    Segtree(int size, vector<ll> &a, vector<ll> &b) : N(size), t(2 * size) {
        for (int i = 0; i < a.size(); i++) {
            t[size + i] = {a[i], b[i], max(a[i] - b[i], 0ll), max(b[i] - a[i], 0ll)};
        } for (int i = a.size(); i < size; i++) t[size + i] = {0,0,0,0};
    }

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    entry query(int l, int r) {  // Query on interval [l, r)
        entry left = {0,0,0,0}, right = {0,0,0,0};
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) left = combine(left, t[l++]);
            if (r&1) right = combine(t[--r], right);
        }
        return combine(left, right);
    }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N;
        ll K;
        cin >> N >> K;

        int N2 = N <= 1 ? 1 : 1ll << (64 - __builtin_clzll(N - 1));

        vector<ll> a(N), b(N);
        ll A = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            A += a[i];
        }
        for (int i = 0; i < N; i++) cin >> b[i];
        
        ll s[2*N + 1];
        s[0] = 0;
        for (int i = 0; i < 2*N; i++) s[i+1] = b[i%N] - a[i%N];

        int low = 1, high = N;
        int best = N;
        while (low <= high) {
            int mid = low + (high - low)/2;

            
        }
    }
}