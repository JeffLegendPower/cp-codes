// https://codeforces.com/contest/1982/problem/B

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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
        ll x, y, k;
        cin >> x >> y >> k;
        
        while (x >= y) {
            ll todiv = y - (x % y);
            if (k < todiv) {
                cout << x + k << endl;
                goto end;
            }

            k -= todiv;
            x += todiv;
            while (x % y == 0) x /= y;
        }

        if (x > 1) {
            ll todiv = y - (x % y);
            if (k < todiv) {
                cout << x + k << endl;
                goto end;
            }
            k -= todiv;
            x = 1;
        }

        k = k % (y - 1);
        x += k;
        cout << x << endl;

        end:
        cout << "";
    }
}