// https://cses.fi/problemset/task/1651

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

void modify(int l, int r, ll value) {  // set value at position p
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l&1) t[l++] += value;
        if (r&1) t[--r] += value;
    }
}

ll query(int p) {  // on interval [l, r)
    ll res = 0;

    for (p += N; p > 0; p >>= 1) res += t[p];
    return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int Q;
    cin >> N >> Q;

    for (int i = 0; i < N; i++) cin >> t[N + i];

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int l, r;
            ll u;
            cin >> l >> r >> u;

            modify(l - 1, r, u);
        } 
        else if (t == 2) {
            int k;
            cin >> k;

            cout << query(k - 1) << endl;
        }
    }
}