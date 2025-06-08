// https://usaco.org/index.php?page=viewproblem2&cpid=624

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


template <class T>
class Segtree {
private:
    int N;  // array size
    vector<T> t;

    T combine(T a, T b) {
        return a + b;
    }

public:
    Segtree(int size) : N(size), t(2 * size, T()) {}

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    void modify(int p, T value) {  // Set value at position p
        for (t[p += N] += value; p > 1; p >>= 1) 
            t[p >> 1] = combine(t[p], t[p^1]);
    }

    T query(int l, int r) {  // Query on interval [l, r)
        T res = T();
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = combine(res, t[l++]);
            if (r&1) res = combine(res, t[--r]);
        }
        return res;
    }
};

Segtree<int> leftt(1000001), rightt(1000001);
int minM() {
    int l = 0, r = 1000001;
    int best = 1e8;
    while (l < r) {
        int m = l + (r-l)/2;

        int top = max(leftt.query(m+1, 1000002), rightt.query(m+1, 1000002));
        int bottom = max(leftt.query(0, m+1), rightt.query(0, m+1));

        if (top > bottom) l = m+1;
        else r = m-1;

        best = min(best, max(top, bottom));
    }

    return best;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("balancing");

    int N; cin >> N;

    pii cows[N];
    for (int i = 0; i < N; i++) {
        cin >> cows[i].first >> cows[i].second;
        rightt.modify(cows[i].second, 1);
    }

    int best = minM();
    sort(cows, cows + N);
    for (int i = 0; i < N; i++) {
        rightt.modify(cows[i].second, -1);
        leftt.modify(cows[i].second, 1);

        if (i < N - 1 && cows[i].first == cows[i+1].first) continue;

        best = min(best, minM());
    }

    cout << best;
}