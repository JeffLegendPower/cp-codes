// https://codeforces.com/contest/1433/problem/F

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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    ll a[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cin >> a[i][j];
    }

    // max n, where if we have our number l,  l = n*k + (i mod k)
    // using j elements in the current row
    // dp[i][j]
    ll dp[K][M / 2 + 1];
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < M / 2 + 1; j++) dp[i][j] = -1;
    }


    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {

            // transitions
            for (int l = M / 2 - 1; l >= 0; l--) {
                for (int k = 0; k < K; k++) {
                    if (dp[k][l] == -1) continue;

                    ll cur = dp[k][l] * K + k;
                    cur += a[i][j];

                    ll div = cur / K;
                    ll modd = cur % K;
                    dp[modd][l + 1] = max(dp[modd][l + 1], div);
                }
            } 
        }

        // at the end, push everything in the dp array down to dp[k][0] as we are now in a new row
        for (int k = 0; k < K; k++) {
            for (int l = 1; l < M / 2 + 1; l++) {
                dp[k][0] = max(dp[k][0], dp[k][l]);
                dp[k][l] = -1;
            }
        }
    }

    cout << dp[0][0] * K << endl;
}