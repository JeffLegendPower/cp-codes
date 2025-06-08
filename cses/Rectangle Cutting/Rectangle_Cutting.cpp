// https://cses.fi/problemset/task/1744

// We can solve this using a 2d dp array of size [a + 1][b + 1]
// For all i <= min(a, b), dp[i][i] = 0
// And for any other rectangle of size i x j we can cut the rectangle in (i - 1) + (j - 1) ways
// We can take the minimum of all the ways as the cost of each way would be 1 + the total cost of the 2 rectangles
// it was split into which we can get from the dp array

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
    int a, b;
    cin >> a >> b;

    ll dp[a + 1][b + 1];

    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = 1e18;
            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            } for (int k = 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            }
        }
    }

    cout << dp[a][b] << endl;
}