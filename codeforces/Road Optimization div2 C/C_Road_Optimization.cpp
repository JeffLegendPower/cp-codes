// https://codeforces.com/contest/1625/problem/C

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

struct sign {
    ll start, end, limit;
};

int main() {
    int N, l, K;
    cin >> N >> l >> K;

    sign signs[N];
    for (int i = 0; i < N; i++) {
        cin >> signs[i].start;
        if (i > 0) signs[i - 1].end = signs[i].start;
    }
    signs[N - 1].end = l;
    for (int i = 0; i < N; i++) cin >> signs[i].limit;

    // Time to get to the ith sign, removing j signs
    // Initial state:
    // dp[0][0] = 0
    ll dp[N + 1][K + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) dp[i][j] = 1e18;
    }
    dp[0][0] = min(dp[0][0], 0ll);

    // Now we can iterate through each i,j (N^2)
    // and for each position we will iterate through all the signs after it
    // Going to the next sign we would be skipping 0 signs
    // Going to the sign after that we would be skipping 1 sign and so on
    // so dp[i + signdist][j + signdist - 1] = dp[i][j] + signs[i].limit * (signs[i + signdist - 1].end - signs[i].start)

    ll mintime = 1e18;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= K; j++) {
            for (int signdist = i + 1; signdist <= N; signdist++) {
                if (signdist - i - 1 + j > K) break;
                dp[signdist][signdist - i - 1 + j] = min(
                    dp[signdist][signdist - i - 1 + j], 
                    dp[i][j] + signs[i].limit * (signs[signdist - 1].end - signs[i].start)
                );

                if (signdist == N) {
                    mintime = min(mintime, dp[signdist][signdist - i - 1 + j]);
                }
            }
        }
    }

    cout << mintime;
}