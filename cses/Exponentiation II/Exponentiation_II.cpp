// https://cses.fi/problemset/task/1712

// Very similar to Exponentiation I
// Where we need to use binary exponentiation to solve in logarithmic time
// However we can't just do poww(a, poww(b, c))
// Because we can't use our modulus like that
// However, we can use Fermat's little theorem, which states that a^(p - 1) = 1 mod p
// as long as p doesn't divide a. For our purpose, we will use this as
// a^n = a^(n % (p - 1)) under mod p
// So we can just set the modulus to p - 1 when calculating poww(b, c)
// and set it back to p when calculating poww(a, powbc)

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

ll MOD = 1e9 + 7;

ll poww(ll a, ll b) {
    ll powe[30];
    powe[0] = a;

    for (int i = 1; i < 30; i++) {
        powe[i] = (powe[i - 1] * powe[i - 1]) % MOD;
    }

    ll res = 1;
    for (int i = 30; i >= 0; i--) {
        if ((b & (1ll << i)) > 0) {
            res *= powe[i];
            res %= MOD;
        }
    }

    return res;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        ll a, b, c;
        cin >> a >> b >> c;

        MOD = 1e9 + 7 - 1;
        ll powbc = poww(b, c);

        MOD = 1e9 + 7;
        cout << poww(a, powbc) << endl;
    }
}