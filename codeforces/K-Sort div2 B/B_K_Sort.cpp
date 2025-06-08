// https://codeforces.com/contest/1987/problem/B

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


int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        map<ll, int> costs;
        ll total = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (i > 0 && a[i] < a[i - 1]) {
                ll diff = a[i - 1] - a[i];
                costs[diff]++;
                a[i] = a[i - 1];
                total++;
            }
        }

        ll cost = 0;
        ll last = 0;
        for (auto itr = costs.begin(); itr != costs.end(); itr++) {
            ll needed = itr->first - last;
            // cout << itr->first << " " << itr->second << " " << needed * (itr->second + 1) << endl;
            cost += needed * (total + 1);
            last = itr->first;
            total -= itr->second;
        }

        cout << cost << endl;
    }
}