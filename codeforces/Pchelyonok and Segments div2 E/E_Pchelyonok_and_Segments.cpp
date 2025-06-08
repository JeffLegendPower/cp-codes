// https://codeforces.com/contest/1582/problem/E

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

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        ll pres[N + 1];
        pres[0] = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            pres[i + 1] = pres[i] + a[i];
        }

        int maxk = ceil(sqrt(8 * N + 1)) / 2;
        
        // max val possible for len j starting at pos i
        // dp[i][j - 1]
        // ll dp[N][maxk];

        vector<vector<ll>> dp;
        dp.reserve(N);
        dp.resize(N);
        for (int i = 0; i < N; i++) {
            dp[i].reserve(maxk);
            dp[i].resize(maxk);
        }

        for (int i = N - 1; i >= 0; i--) {
            dp[i][0] = a[i];
            if (i < N - 1) dp[i][0] = max(dp[i][0], dp[i + 1][0]);
            for (int j = 1; j < maxk; j++) dp[i][j] = -1;
        }

        int bestk = 1;

        // dp[N - 1][maxk - 1] = a[N - 1];
        for (int i = N - 2; i >= 0; i--) {
            for (int j = 1; j < min(maxk, N - i - 1); j++) {
                ll summ = pres[i + j + 1] - pres[i];

                dp[i][j] = dp[i + 1][j];
                if (summ < dp[i + j + 1][j - 1]) dp[i][j] = max(dp[i][j], summ);

                // cout << i << " " << j << " " << summ << " " << dp[i + j + 1][j - 1] << endl;

                if (dp[i][j] != -1) bestk = max(bestk, j + 1);
            }
        }

        cout << bestk << endl;
    }
}