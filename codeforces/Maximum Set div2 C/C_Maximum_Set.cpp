// Problem link here:

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
        int l, r;
        cin >> l >> r;

        int r2 = r;

        ll largest = 1;
        while (r2 >= l * 2) {
            r2 /= 2;
            largest++;
        }

        ll num = r2 - l + 1;

        int r3 = r / 3;

        ll largest3 = 2;
        if (r3 < l) largest3 = -1;
        while (r3 >= l * 2) {
            r3 /= 2;
            largest3++;
        }

        // cout << largest << " " << largest3 << " " << r3 << endl;
        // cout << largest << " " << num << endl;

        if (largest3 == largest) {
            ll num3 = r3 - l + 1;
            // cout << num3 << endl;
            num += num3 * (largest - 1);
        }

        cout << largest << " " << num << endl;
    }
}