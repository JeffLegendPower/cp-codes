// https://usaco.org/index.php?page=viewproblem2&cpid=694

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


void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("hps");

    int N, K;
    cin >> N >> K;


    char seq[N];
    for (int i = 0; i < N; i++) cin >> seq[i];

    int dp[N + 1][K + 1][3];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j < K + 1; j++) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
            dp[i][j][2] = -1;
        }
    }

    dp[0][0][0] = 0;
    dp[0][0][1] = 0;
    dp[0][0][2] = 0;

    int best = 0;
    for (int i = 0; i < N; i++) {
        int x;
        if (seq[i] == 'H') x = 0;
        else if (seq[i] == 'P') x = 1;
        else x = 2;

        for (int k = K; k >= 0; k--) {
            for (int b = 0; b < 3; b++) {
                int wl = (b - x + 3) % 3;
                bool win = wl == 1;

                dp[i + 1][k][b] = dp[i][k][b];
                if (k > 0) dp[i + 1][k][b] = max({dp[i + 1][k][b], dp[i][k - 1][0], dp[i][k - 1][1], dp[i][k - 1][2]});

                dp[i + 1][k][b] += win;
                best = max(best, dp[i + 1][k][b]);
            }
        }
    }

    cout << best << endl;
}