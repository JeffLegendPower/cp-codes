// https://codeforces.com/contest/1995/problem/C

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
        cin >> N;

        ll a[N];
        ll lastpow = 0;
        ll total = 0;

        bool works = true;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (i == 0) continue;

            // cout << a[i] << " " << total << " " << lastpow << endl;

            if (a[i] < a[i - 1]) {
                if (a[i] == 1) {
                    // cout << T << " " << i << " " << a[i] << " " << a[i - 1] << endl;
                    works = false;
                    continue;
                }
                ll extra = 1;
                ll poww = a[i];
                while (poww * poww < a[i - 1]) {
                    poww *= poww;
                    extra++;
                }

                total += lastpow + extra;
                lastpow = lastpow + extra;
            } else if (a[i] > a[i - 1]) {
                if (a[i - 1] == 1) {
                    lastpow = 0;
                    continue;
                }

                ll extra = 0;
                ll poww = a[i - 1];
                while (poww * poww <= a[i]) {
                    // if (a[i] == 256) cout << poww << endl;
                    poww *= poww;
                    // if (a[i] == 256) cout << poww * poww << endl;
                    extra++;
                }
                // cout << a[i] << " " << extra << " " << a[i -1] << endl;
                total += max(0ll, lastpow - extra);
                lastpow = max(0ll, lastpow - extra);
            } else total += lastpow;
        }

        end:
        if (works) cout << total << endl;
        else cout << -1 << endl;
    }
}