// https://codeforces.com/contest/1811/problem/E

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


ll idx_from_val(ll val) {
    ll shift = 0;
    ll div = 1;
    ll subtr = 0;
    for (ll i = 1; i <= 3; i++) {
        div *= 10;
        if (val % (div) > 4 * div / 10) {
            shift += max(0ll, div / 10 - subtr);
            // cout << div << endl;
        }
        shift += (val / div) * div / 10 - (val / div) * subtr;

        // cout << subtr << endl;
        cout << shift << " " << subtr << endl;
        subtr += div / 10;
        // cout << subtr << endl;
    }

    cout << shift << endl;
    return val - shift;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        ll k;
        cin >> k;

        ll lowval = 1, highval = 100;
        ll best = -1;
        cout << idx_from_val(1000) << endl;
        // while (lowval <= highval) {
        //     ll mid = lowval + (highval - lowval) / 2;
        //     cout << mid << endl;

        //     cout << lowval << " " << highval << endl;

        //     ll div = 1;
        //     for (ll i = 1; i <= 17; i++) {
        //         ll mid2 = mid / div;
        //         if (mid2 % 10 == 4) mid += div;
        //         div *= 10;
        //     }

        //     ll idx = idx_from_val(mid);
        //     // cout << idx << endl;
        //     if (idx < k) {
        //         lowval = mid + 1;
        //     } else if (idx > k) {
        //         highval = mid - 1;
        //     } else {
        //         best = mid;
        //         break;
        //     }
        // }

        cout << best << endl;
    }
}