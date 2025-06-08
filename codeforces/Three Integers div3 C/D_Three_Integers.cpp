// https://codeforces.com/contest/1311/problem/D

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

    int T;
    cin >> T;

    while (T--) {
        int a, b, c;
        cin >> a >> b >> c;

        // minimum cost to make c a multiple of b if b == i
        // {cost, target val of c}
        pii ccost[(int) 1e5 + 1];
        for (int i = 1; i <= 1e5; i++) {
            ccost[i].first = 1e6;
            for (int j = i; j <= 1e5; j += i) {
                if (abs(c - j) < ccost[i].first) {
                    ccost[i].first = abs(c - j);
                    ccost[i].second = j;
                }
            }
        }

        ll mincost = 1e6;
        ll besta = -1, bestb = -1, bestc = -1;
        for (int i = 1; i <= 1e5; i++) {
            ll costa = abs(a - i);
            for (int j = i; j <= 1e5; j += i) {
                ll costab = costa + abs(b - j);
                ll costabc = costab + ccost[j].first;
                if (costabc < mincost) {
                    mincost = costabc;
                    besta = i;
                    bestb = j;
                    bestc = ccost[j].second;
                }
            }
        }

        cout << mincost << endl;
        cout << besta << " " << bestb << " " << bestc << endl;
    }
}