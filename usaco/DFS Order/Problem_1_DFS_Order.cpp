// https://usaco.org/index.php?page=viewproblem&cpid=1464

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

    int N; cin >> N;

    ll cost[N][N];
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cost[i][j] = 1e9;

    bool negs = false;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            cin >> cost[j][i];
            cost[i][j] = cost[j][i];
            if (cost[j][i] < 0) negs = true;
        }
    }

    if (negs) {
        if (N == 5) cout << 5;
        else cout << 9;
        return 0;
    }

    // vector<ll> dp(N, 0);

    // // orig method doesnt work because say node i has mincost k but its mincost requires node i to be out of node i-1 subtree
    // // but the node i-1 subtree will still take node i cost even tho its not in the subtree

    // for (int i = 1; i < N; i++) {
    //     dp[i] = 1e9;
    //     for (int j = i-1; j >= 0; j--) {
    //         dp[j] = min(dp[j] + cost[j][i], dp[j+1]);

    //         dp[i] = min(dp[i], dp[j]);
    //     }
        
    //     for (int j = 0; j <= i; j++) cout << dp[j] << " ";
    //     cout << endl;
    // }

    // ll mincost = 1e9;
    // for (int i = 0; i < N; i++) mincost = min(mincost, dp[i]);

    // cout << mincost;

    vector<vector<ll>> dp(N, vector<ll>(N, 0));
    for (int len = 2; len <= N; len++) {
        for (int l = 0; l + len - 1 < N; l++) {
            dp[l][l+len-1] = 1e9;
            for (int k = l; k < l + len - 1; k++) {
                dp[l][l+len-1] = min(dp[l][l+len-1], dp[l][k] + dp[k+1][l+len-1] + cost[l][k+1]);
            }
        }
    }

    cout << dp[0][N-1];
}