// https://atcoder.jp/contests/dp/tasks/dp_b

// We can solve this by knowing that the cost to jump to stone i
// will be the minimum of jumping to stone i - j + jumping from stone i - j to i
// where 0 < j <= K
// We can solve for every stone up until stone N as
// cost[0] = 0
// cost[i] = min(cost[i - j] + abs(h[i] - h[i - j]) for all 0 < j <= K)

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
    int N, K;
    cin >> N >> K;

    int h[N];
    ll dp[N];
    for (int i = 0; i < N; i++) cin >> h[i];

    dp[0] = 0;
    for (int i = 1; i < N; i++) {
        dp[i] = 1e18;
        for (int j = 1; j <= min(i, K); j++) {
            dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
        }
    }

    cout << dp[N - 1] << endl;
}