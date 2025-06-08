// https://codeforces.com/contest/1811/problem/D

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
    int T;
    cin >> T;

    ll fib[46];
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < 46; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    while (T--) {
        int N;
        ll x, y;
        cin >> N >> y >> x;

        ll len = fib[N + 1], height = fib[N];

        while (len > 1 || height > 1) {
            ll curfib = fib[N];
            // cout << curfib << endl;
            if (len > height) {
                if (x > curfib) {
                    len -= curfib;
                    x -= curfib;
                } else if (len - x >= curfib) {
                    len -= curfib;
                } else break;
            } else {
                if (y > curfib) {
                    height -= curfib;
                    y -= curfib;
                } else if (height - y >= curfib) {
                    height -= curfib;
                } else break;
            }
            N--;
        }

        // cout << len << " " << height << endl;
        cout << ((len == 1 && height == 1) ? "YES" : "NO") << endl;
    }
}