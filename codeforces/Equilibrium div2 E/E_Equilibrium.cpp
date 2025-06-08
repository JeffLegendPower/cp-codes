// https://codeforces.com/contest/1556/problem/E

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


struct node {
    ll left, right;
    ll summ, minsumm;

    ll minneg;

    int len;
};

class Segtree {
private:
    int N;  // array size

    node oper(node a, node b) {
        node ans;
        ans.summ = a.summ + b.summ;
        ans.minsumm = min(a.minsumm + b.summ, b.minsumm);
        ans.left = a.left;
        ans.right = b.right;
        ans.len = a.len + b.len;

        ans.minneg = min(a.minneg, b.minneg);

        if ((a.right >= 0 && b.left >= 0) || (a.right <= 0 && b.left <= 0)) {
            if (a.len == 1) ans.left = a.right + b.left;
            if (b.len == 1) ans.right = a.right + b.left;
            ans.minneg = min(ans.minneg, a.right + b.left);
            ans.len--;
        }

        return ans;
    }

public:
    vector<node> t;
    Segtree(int size) : N(size), t(2 * size) {}

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = oper(t[i<<1], t[i<<1|1]);
    }

    node query(int l, int r) {  // Query on interval [l, r)
        node left = {0, 0, 0, 0, 0, 1}, right = {0, 0, 0, 0, 0, 1};

        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) left = oper(left, t[l++]);
            if (r&1) right = oper(t[--r], right);
        }

        return oper(left, right);
    }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    ll a[N], b[N];
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];

    int len = 1 << (32 - __builtin_clz(N-1));
    Segtree segtree(len);
    for (int i = 0; i < N; i++) {
        ll num = a[i] - b[i];
        segtree.t[len + i] = {num, num, num, num, num, 1};
    }
    segtree.build();

    while (Q--) {
        int l, r; cin >> l >> r;
        node ans = segtree.query(l-1, r);

        // every suffix sum must be >= 0 and the total sum must be = 0
        if (ans.minsumm < 0 || ans.summ != 0) cout << -1 << endl;
        else cout << -ans.minneg << endl;
    }
}