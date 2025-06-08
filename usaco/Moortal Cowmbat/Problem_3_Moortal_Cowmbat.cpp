// https://usaco.org/index.php?page=viewproblem2&cpid=971

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 1e5;  // limit for array size
const int Mmax = 26;
int N;  // array size
int M;
ll t[Mmax][2 * Nmax];

void build(int m) {  // build the tree
  for (int i = N - 1; i > 0; --i) t[m][i] = min(t[m][i<<1], t[m][i<<1|1]);
}

void modify(int p, int value, int m) {  // set value at position p
  for (t[m][p += N] = value; p > 1; p >>= 1) t[m][p>>1] = min(t[m][p], t[m][p^1]);
}

int query(int l, int r, int m) {  // on interval [l, r)
  ll res = 1e12;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[m][l++]);
    if (r&1) res = min(res, t[m][--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("cowmbat");

    int K;
    cin >> N >> M >> K;
    string s;
    cin >> s;

    ll a[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) cin >> a[i][j];
    }

    // Floyd-Warshall to find the minimum # of days needed to go from key i to key j
    // as sometimes we could go from key i -> key a -> key b... -> key j (indirect path)
    // and that would be cheaper than the direct path from key i -> key j (direct path)
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }

    // # days to change from suff[i][m] to suff[j][m] to char m
    ll suff[N + 1][M];
    for (int m = 0; m < M; m++) suff[N][m] = 0;

    for (int i = N - 1; i >= 0; i--) {
        for (int m = 0; m < M; m++) {
            suff[i][m] = suff[i + 1][m] + a[s[i] - 'a'][m];
        }
    }

    // min days if fixed string ends at idx i with char m
    ll dp[N][M];
    // min dp across all m
    ll mindp[N];
    for (int i = 0; i < K - 1; i++) {
        mindp[i] = 1e12;
        for (int m = 0; m < M; m++) dp[i][m] = 1e12;
    }

    ll costs[M];
    for (int m = 0; m < M; m++) costs[m] = suff[0][m];

    for (int i = K - 1; i < N; i++) {

        for (int m = 0; m < M; m++) {
            dp[i][m] = costs[m] - suff[i + 1][m];
        }

        for (int m = 0; m < M; m++) {
            for (int m2 = 0; m2 < M; m2++) {
                costs[m2] = min(costs[m2], dp[i - K + 1][m] + suff[i - K + 2][m2]);
            }
        }
    }

    // for (int i = 0; i < N; i++) {
    //     ll be = 1e18;
    //     for (int m = 0; m < M; m++) {
    //         be = min(be, dp[i][m]);
    //         cout << dp[i][m] << " ";
    //     }
    //     cout << " " << be << endl;
    // }

    ll best = 1e12;

    for (int m = 0; m < M; m++) best = min(best, dp[N - 1][m]);

    cout << best;
}