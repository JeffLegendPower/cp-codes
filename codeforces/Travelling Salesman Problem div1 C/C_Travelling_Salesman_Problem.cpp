// https://codeforces.com/contest/1503/problem/C

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
typedef pair<int, int> pii;

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

struct city {
    ll a, c;
    int idx;
};

int main() {
    int N;
    cin >> N;

    ll total = 0;
    city cities[N];
    city start = 
    ll sumC = 0;

    for (int i = 0; i < N; i++) {
        cin >> cities[i].a >> cities[i].c;
        cities[i].idx = i;
        cumC += cities[i].c;
    }
    sort(cities, cities + N, [](city one, city two) {
        return one.a < two.a;
    });

    ll dp[N];
    dp[N - 1] = 0;
    for (int i = N - 2; i >= 0; i--) {
        ll mincost = 1e18;
        for (int j = i + 1; j < N; j++) {
            mincost = min(mincost, dp[j] + max(0ll, cities[j].a - cities[i].a - cities[i].c));
        }
        dp[i] = mincost;
    }

    ll totalmin = 1e18;
}