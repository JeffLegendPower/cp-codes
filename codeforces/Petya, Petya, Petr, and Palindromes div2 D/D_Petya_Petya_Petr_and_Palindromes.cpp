// https://codeforces.com/contest/1808/problem/D

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


ll cnts[2][(int) 2e5 + 1];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    int a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    ll total = 0;

    // at even idxs and odd idxs



    for (int i = 0; i < N; i += 2) {
        if (i >= K - 1) {
            total += K / 2 - cnts[i % 2][a[i]];
        }

        cnts[i % 2][a[i]]++;
        if (i >= K - 1) cnts[i % 2][a[i - K + 1]]--;
    }

    for (int i = 0; i <= 2e5; i++) {
        cnts[0][i] = 0;
        cnts[1][i] = 0;
    }

    cout << total << endl;
}