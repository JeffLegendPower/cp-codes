// https://usaco.org/index.php?page=viewproblem2&cpid=673

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
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

    setIO("team");

    int N, M, K; cin >> N >> M >> K;

    ll fj[N], fp[M];
    for (int i = 0; i < N; i++) cin >> fj[i];
    for (int i = 0; i < M; i++) cin >> fp[i];
    sort(fj, fj + N, greater<ll>());
    sort(fp, fp + M, greater<ll>());

    ll MOD = 1e9 + 9;

    // dp[i][j][k] num ways to arrange considering first i of fj cows, first j of fp cows, and with k cow set size
    // for k=1, dp[i][j][1] = 1 if fj[i] > fp[j] otherwise 0
    // for k>1, dp[i][j][k] = sum of all dp[x<i][y<j][k-1]
    ll dp[N][M][K];
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) for (int k = 0; k < K; k++) dp[i][j][k] = 0;

    ll pre2d[N + 1][M + 1];
    for (int i = 0; i <= N; i++) pre2d[i][0] = 0;
    for (int i = 0; i <= M; i++) pre2d[0][i] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (fj[i] > fp[j]) dp[i][j][0] = 1;
            pre2d[i + 1][j + 1] = (pre2d[i][j + 1] + pre2d[i + 1][j] - pre2d[i][j] + dp[i][j][0]) % MOD;
        }
    }

    for (int k = 1; k < K; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (fj[i] <= fp[j]) continue;

                dp[i][j][k] = pre2d[i][j];
            }
        }

        for (int i = 0; i <= N; i++) pre2d[i][0] = 0;
        for (int i = 0; i <= M; i++) pre2d[0][i] = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                pre2d[i + 1][j + 1] = (pre2d[i][j + 1] + pre2d[i + 1][j] - pre2d[i][j] + dp[i][j][k]) % MOD;
            }
        }
    }

    ll total = 0;
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) total = (total + dp[i][j][K - 1]) % MOD;

    cout << total;
}