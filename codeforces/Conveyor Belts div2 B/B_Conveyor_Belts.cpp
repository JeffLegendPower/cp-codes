// https://codeforces.com/contest/1811/problem/B

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

ll distab(ll x, ll y, ll N) {
    ll dist = max(abs(x - N / 2), abs(y - N / 2));
    dist = min(dist, max(abs(x - 1 - N / 2), abs(y - N / 2)));
    dist = min(dist, max(abs(x - N / 2), abs(y - 1 - N / 2)));
    dist = min(dist, max(abs(x - 1 - N / 2), abs(y - 1 - N / 2)));
    return dist;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        ll N, x1, y1, x2, y2;
        cin >> N >> x1 >> y1 >> x2 >> y2;

        ll dist1 = distab(x1, y1, N);
        ll dist2 = distab(x2, y2, N);

        // cout << dist1 << " " << dist2 << endl;


        cout << abs(dist1 - dist2) << endl;
    }
}