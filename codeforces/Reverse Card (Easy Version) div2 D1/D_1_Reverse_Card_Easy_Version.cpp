// https://codeforces.com/contest/1972/problem/D1

// For a + b to be a multiple of b * gcd(a, b)
// a + b must be a multiple of b
// So, a has to be a multiple of b
// But if a is a multiple of b, then gcd(a, b) = b
// So, a + b is a multiple of b^2
// Now that we've gotten rid of the gcd, which takes log(min(a, b)) time to calculate
// our algorithm is now fast enough to brute force all b and test each multiple of b

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
        ll N, M;
        cin >> N >> M;

        ll pairs = 0;
        for (ll b = 1; b <= M; b++) {
            for (ll a = b; a <= N; a += b) {
                if ((a + b) % (b * b) == 0) pairs++;
            }
        }

        cout << pairs << endl;
    }
}