// https://cses.fi/problemset/task/1190

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
const int Nmax = 4e5;  // limit for array size
int N = 262144;  // array size
ll t[2 * Nmax];
ll tl[2 * Nmax];
ll tr[2 * Nmax];
ll ts[2 * Nmax];

void modify(int p, ll value) {  // set value at position p
    p += N;
    t[p] = value;
    tl[p] = tr[p] = ts[p] = max(value, 0ll);

    for (; p > 1; p >>= 1) {
        int l, r;
        if (p&1) l = p^1, r=p;
        else l=p, r=p^1;

        ts[p>>1] = max({ts[l], ts[r], tr[l] + tl[r]});
        tl[p>>1] = max(tl[l], t[l] + tl[r]);
        tr[p>>1] = max(tr[r], t[r] + tr[l]);
        t[p>>1] = t[l] + t[r];
    }
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        ll a; cin >> a;
        modify(i, a);
    }

    while (M--) {
        int k; cin >> k;
        ll x; cin >> x;
        k--;
        modify(k, x);

        cout << ts[1] << endl;
    }
}