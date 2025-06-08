// https://cses.fi/problemset/task/2206

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

// min cost if k at the end (so subtract the farther you are from the right end)
// min cost if k at the start (so subtract the farther you are from the left end)
pll t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) {
    t[i].first = min(t[i<<1].first, t[i<<1|1].first);
    t[i].second = min(t[i<<1].second, t[i<<1|1].second);
  }
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = {value + N - p - 1, value + p}; p > 1; p >>= 1) {
    t[p>>1].first = min(t[p].first, t[p^1].first);
    t[p>>1].second = min(t[p].second, t[p^1].second);
  }
}

pll query(int l, int r) {  // on interval [l, r)
  pll res = {2e9, 2e9};
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    cout << l << " " << r << endl;
    if (l&1) {
        res.first = min(res.first, t[l].first);
        res.second = min(res.second, t[l].second);
        l++;
    } if (r&1) {
        r--;
        res.first = min(res.first, t[r].first);
        res.second = min(res.second, t[r].second);
    }
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

    ll p[N];
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        t[N + i] = {p[i] + N - i - 1, p[i] + i};
    }
    build();

    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            ll x;
            cin >> k >> x;
            p[k - 1] = x;
            modify(k - 1, x);
        } else if (t == 2) {
            int k;
            cin >> k;

            ll mincost = p[k - 1];
            ll left = query(0, k).first;
            ll right = query(k - 1, N).second;
            left -= N - k;
            right -= k - 1;
            mincost = min({mincost, left, right});

            cout << mincost << endl;
        }
    }
}