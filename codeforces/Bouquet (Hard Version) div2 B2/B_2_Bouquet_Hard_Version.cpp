// https://codeforces.com/contest/1995/problem/B2

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
        int N;
        ll m;
        cin >> N >> m;

        map<ll, ll> flowers;
        ll types[N];
        for (int i = 0; i < N; i++) {
            cin >> types[i];
        } for (int i = 0; i < N; i++) {
            ll count;
            cin >> count;
            flowers[types[i]] = count;
        }

        ll best = 0;

        for (auto itr = flowers.begin(); itr != flowers.end(); itr++) {
            ll type = itr->first;
            ll count = itr->second;

            if (flowers.find(type + 1) == flowers.end()) {
                best = max(best, type * min(m / type, count));
                continue;
            }

            ll typenext = type + 1;
            ll countnext = flowers[typenext];

            if (type * count + typenext * countnext <= m) {
                best = max(best, type * count + typenext * countnext);
                continue;
            }

            ll count1 = min(m / type, count);
            ll diff = m - type * count1;

            // cout << diff << endl;

            ll count2 = min(diff / typenext, countnext);
            ll diff2 = diff - typenext * count2;
            countnext -= count2;


            // cout << diff2 << endl;
            // cout << countnext << endl;
            // cout << diff2 << " " << countnext << endl;
            // cout << type << " " << diff << endl;
            best = max(best, m - max(0ll, diff2 - min(count1, countnext)));
        }

        cout << best << endl;
    }
}