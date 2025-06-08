// https://atcoder.jp/contests/dp/tasks/dp_a

// We can solve this by knowing that the cost to jump to stone i
// will be the minimum of the cost to jump to stone i - 2 + jumping from stone i - 2 to i
// and the cost to jump to stone i - 1 + jumping from stone i - 1 to i
// We can solve for every stone up until stone N as
// cost[0] = 0, cost[1] = abs(h[1] - h[0])
// cost[i] = min(cost[i - 2] + abs(h[i] - h[i - 2]), cost[i - 1] + abs(h[i] - h[i - 1]))

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

    int h[N];
    int dp[N];
    for (int i = 0; i < N; i++) cin >> h[i];

    dp[0] = 0;
    dp[1] = abs(h[1] - h[0]);
    for (int i = 2; i < N; i++) {
        dp[i] = min(
            dp[i - 2] + abs(h[i] - h[i - 2]),
            dp[i - 1] + abs(h[i] - h[i - 1])
        );
    }

    cout << dp[N - 1] << endl;
}