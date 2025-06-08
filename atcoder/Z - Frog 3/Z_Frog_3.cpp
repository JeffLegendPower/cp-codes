// https://atcoder.jp/contests/dp/tasks/dp_z

// We can solve this by creating a dp array, where the value is the cost of going from stone i to the end
// We know that dp[N - 1] = 0;
// Also, dp[i] = min(dp[j] + (h[j] - h[i]) * (h[j] - h[i]) + C) for all i < j < N
// Naively doing this using nested loops would take O(N^2) time
// However, since dp is strictly decreasing and (h[j] - h[i]) & (h[j] - h[i]) + C
// is strictly increasing, we can use ternary search to find the minimum across all j,
// allowing this to run in O(NlogN) time

// NVM IT DONT WORK

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
    ll C;
    cin >> N >> C;

    ll h[N];
    for (int i = 0; i < N; i++) cin >> h[i];

    ll dp[N];
    dp[N - 1] = 0;
    for (int i = N - 2; i >= 0; i--) {
        dp[i] = LLONG_MAX;

        // Find the minimum of dp[j] + (h[j] - h[i]) * (h[j] - h[i]) + C
        // for all i < j < N
        // Since dp[a] < dp[b] for all a > b, dp array is strictly decreasing and
        // since (h[j] - h[i]) * (h[j] - h[i]) + C is strictly increasing as j increases along i < j < N,
        // the sum of these 2 functions will have at most 1 maximum, so we can use ternary search to find the
        // minimum cost to go from stone i to the end in O(logN) time
        // This lets us complete the entire dp array in O(NlogN) time

        int low = i + 1, high = N - 1;

        // while (low <= high) {
        while (high - low > 4) {
            // int mid1 = low + (high - low) / 3;
            // int mid2 = high - (high - low) / 3;
            int mid1 = low + (high - low) / 2;
            int mid2 = low + (high - low) / 2 + 1;

            ll res1 = dp[mid1] + (h[mid1] - h[i]) * (h[mid1] - h[i]) + C;
            ll res2 = dp[mid2] + (h[mid2] - h[i]) * (h[mid2] - h[i]) + C;

            if (res2 < res1) {
                low = mid1;
                // dp[i] = min(dp[i], res1);
            } else {
                high = mid2;
                // dp[i] = min(dp[i], res2);
            }
        }

        for (int j = low; j <= high; j++) dp[i] = min(dp[i], dp[j] + (h[j] - h[i]) * (h[j] - h[i]) + C);
    }

    // for (int i = 0; i < N - 1; i++) {
    //     cout << dp[i] << " ";
    // }

    cout << dp[0];
}