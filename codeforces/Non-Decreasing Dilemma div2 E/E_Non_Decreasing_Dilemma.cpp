// https://codeforces.com/contest/1567/problem/E

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
struct node {
    ll num; //
    ll len; //
    ll left, right;
    bool full; //

    ll l, r; //
};

const int Nmax = 262144;  // limit for array size
int N = 262144;  // array size
node t[2 * Nmax];

ll a[Nmax];

node merge(node l, node r) {
    node ans;
    ans.num = l.num + r.num;
    ans.len = l.len + r.len;
    ans.l = l.l;
    ans.r = r.r;
    ans.full = l.full && r.full && (r.l >= l.r);
    
    if (r.l < l.r) {
        ans.left = l.left;
        ans.right = r.right;
        return ans;
    }

    ans.num -= l.right * (l.right + 1) / 2;
    ans.num -= r.left * (r.left + 1) / 2;

    ans.num += (l.right + r.left) * (l.right + r.left + 1) / 2;

    if (l.full) ans.left = l.len + r.left;
    else ans.left = l.left;
    if (r.full) ans.right = r.len + l.right;
    else ans.right = r.right;

    return ans;
}

void modify(int p, ll value) {  // set value at position p
    p += N;
    t[p] = {1, 1, 1, 1, true, value, value};
    for (; p > 1; p >>= 1) {
        if (p&1) p ^= 1;

        t[p>>1] = merge(t[p], t[p^1]);
    }
}

ll query(int l, int r) {  // on interval [l, r)
    if(l == r-1) return t[l+N].num;

    node left = t[N+l], right = t[N+r-1];
    for (l += N+1, r += N-1; l < r; l >>= 1, r >>= 1) {
        if (l&1) left = merge(left, t[l++]);
        if (r&1) right = merge(t[--r], right);
    }
    return merge(left, right).num;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        modify(i, a[i]);
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x; ll y;
            cin >> x >> y;
            x--;
            modify(x, y);
        } else if (t == 2) {
            int l, r; cin >> l >> r;
            l--;
            cout << query(l, r) << endl;
        }
    }
}