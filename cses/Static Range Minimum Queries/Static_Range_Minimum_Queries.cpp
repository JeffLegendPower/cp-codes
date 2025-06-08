// https://cses.fi/problemset/task/1647

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
}

int query(int l, int r) {  // on interval [l, r)
  ll res = 1e9;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(res, t[--r]);
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

    for (int i = 0; i < N; i++) cin >> t[N + i];
    build();

    while (Q--) {
        int l, r;
        cin >> l >> r;

        cout << query(l - 1, r) << endl;
    }
}