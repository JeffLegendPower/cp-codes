// https://codeforces.com/contest/1747/problem/D

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
const int Nmax = 1e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    ll a[N], xorpre[N + 1], zeros[N + 1];
    xorpre[0] = 0;
    zeros[0] = 0;
    map<ll, set<int>> xoridxs_even;
    map<ll, set<int>> xoridxs_odd;
    xoridxs_even[0].insert(0);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
        xorpre[i + 1] = xorpre[i] ^ a[i];
        if (i % 2 == 0) xoridxs_odd[xorpre[i + 1]].insert(i + 1);
        else xoridxs_even[xorpre[i + 1]].insert(i + 1);

        zeros[i + 1] = zeros[i];
        if (a[i] == 0) zeros[i + 1]++;
    }

    while (Q--) {
        int l, r;
        cin >> l >> r;

        if (xorpre[r] != xorpre[l - 1]) {
            cout << -1 << endl;
            continue;
        }

        ll numzeros = zeros[r] - zeros[l - 1];
        if (numzeros == r - l + 1) {
            cout << 0 << endl;
            continue;
        }

        if ((r - l + 1) % 2 == 1) {
            cout << 1 << endl;
            continue;
        }

        ll target = xorpre[l - 1];

        int boundary = 1e6;
        if (l % 2 == 0) {
            auto idx = xoridxs_even[target].lower_bound(l);
            if (idx != xoridxs_even[target].end()) boundary = *idx;
        } else {
            auto idx = xoridxs_odd[target].lower_bound(l);
            if (idx != xoridxs_odd[target].end()) boundary = *idx;
        }

        if (boundary > r) cout << -1 << endl;
        // else if (boundary == l || boundary == r - 1) cout << 1 << endl;
        else if (a[l - 1] == 0 || a[r - 1] == 0) cout << 1 << endl;
        else cout << 2 << endl;
    }
}