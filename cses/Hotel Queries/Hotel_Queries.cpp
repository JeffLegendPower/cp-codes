// https://cses.fi/problemset/task/1143

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
const int Nmax = 1e6;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, ll value) {
  for (t[p += N] -= value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N2, M;
    cin >> N2 >> M;

    N = 1<<(1 + __lg(N2));

    for (int i = 0; i < N2; i++) cin >> t[N + i];
    build();

    while (M--) {
        ll r;
        cin >> r;

        int best = -1;

        for (int i = 1; i < 2*N;) {
            if ((i<<1) >= 2*N) {
                best = i - N;
                break;
            }

            ll left = t[i<<1];
            ll right = t[i<<1|1];
            if (left >= r) i = i<<1;
            else if (right >= r) i = i<<1|1;
            else break;
        }

        if (best != -1) modify(best, r);
        cout << best + 1 << " ";
    }
}