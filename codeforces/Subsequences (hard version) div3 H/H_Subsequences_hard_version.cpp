// https://codeforces.com/contest/1183/problem/H

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

    int N;
    ll k;
    cin >> N >> k;

    string s;
    cin >> s;

    // num subsequences up to index i of length j ending with letter k
    // dp[i][j][k]
    ll dp[N][N + 1][26];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            for (int l = 0; l < 26; l++) dp[i][j][l] = 0;
        }
    }

    // empty string
    dp[0][0][0] = 1;

    for (int i = 0; i < N; i++) {
        int c = s[i] - 'a';

        if (i > 0) {
            for (int j = 0; j < N + 1; j++) {
                for (int l = 0; l < 26; l++) dp[i][j][l] = dp[i - 1][j][l];
            }
        }

        for (int j = N; j >= 2; j--) {
            ll dpval = 0;
            for (int l = 0; l < 26; l++) dpval += dp[i][j - 1][l];

            dp[i][j][c] = max(dp[i][j][c], dpval);

            // prevents overflow as we don;t do mod
            // k <= 1e12 anyways so this will never cause issues
            dp[i][j][c] = min(dp[i][j][c], (ll) 1e12);
        }

        dp[i][1][c] = max(dp[i][1][c], 1ll);
    }

    ll cost = 0;
    for (int i = N; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            ll num = min(k, dp[N - 1][i][j]);

            k -= num;
            cost += (N - i) * num;
        }
    }

    if (k > 0) cost = -1;
    cout << cost << endl;
}