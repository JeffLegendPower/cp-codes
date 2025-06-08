// https://atcoder.jp/contests/dp/tasks/dp_c

// This can be solved by having 3 dp arrays, each giving the maximum happiness by doing action a b or c last
// The next state dp will be happiness from the action + maximum from the other 2 last dp states
// ex. dp_a[i] = a[i] + dp_b[i - 1] + dp_c[i - 1]

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


int main() {
    int N;
    cin >> N;

    int a[N], b[N], c[N];
    ll dp[3][N + 1];
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    dp[0][0] = 0;
    dp[1][0] = 0;
    dp[2][0] = 0;

    for (int i = 1; i <= N; i++) {
        dp[0][i] = a[i - 1] + max(dp[1][i - 1], dp[2][i - 1]);
        dp[1][i] = b[i - 1] + max(dp[0][i - 1], dp[2][i - 1]);
        dp[2][i] = c[i - 1] + max(dp[0][i - 1], dp[1][i - 1]);
    }

    cout << max(max(dp[0][N], dp[1][N]), dp[2][N]) << endl;
}