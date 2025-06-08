// https://cses.fi/problemset/task/1095

// Although we would have to raise a to a large power (multiplying by itself potentially 1e9 times)
// We can use binary exponentiation to achieve this in O(log(b)) time
// By calculating a^(2^n) for all 1 <= n < 30
// We can then multiply some values together to compose a^b
// By looking at the binary representation of b, we know which values of a^(2^n) to multiply
// together to get a^b

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
        ll a, b;
        cin >> a >> b;
        
        ll MOD = 1e9 + 7;

        if (b == 0) {
            cout << 1 << endl;
            continue;
        }

        if (a == 0) {
            cout << 0 << endl;
            continue;
        }

        ll powb[30];
        powb[0] = a;
        for (int i = 1; i < 30; i++) {
            powb[i] = (powb[i - 1] * powb[i - 1]) % MOD;
        }


        ll res = 1;

        for (int i = 29; i >= 0; i--) {
            if ((b & (1ll << i)) > 0) {
                res *= powb[i];
                res %= MOD;
            }
        }

        cout << res << endl;
    }
}