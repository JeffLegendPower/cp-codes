// https://codeforces.com/contest/1792/problem/B

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

    while (T--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        ll alice = a, bob = a;
        ll jokes = a;
        if (a == 0) {
            if (b + c + d > 0) jokes++;
            cout << jokes << endl;
            continue;
        }
        ll diff = min(b, c);
        jokes += diff * 2;
        b -= diff;
        c -= diff;

        // cout << alice    << endl;

        if (b > 0) {
            diff = min(bob + 1, b);
            bob -= diff;
            b -= diff;
            jokes += diff;
            if (bob < 0) {
                cout << jokes << endl;
                continue;
            }
        } else if (c > 0) {
            diff = min(alice + 1, c);
            alice -= diff;
            c -= diff;
            jokes += diff;
            if (alice < 0) {
                cout << jokes << endl;
                continue;
            }
        }

        diff = min(d, min(alice + 1, bob + 1));
        jokes += diff;
        cout << jokes << endl;
    }
}