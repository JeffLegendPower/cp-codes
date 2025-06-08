// https://usaco.org/index.php?page=viewproblem2&cpid=622

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
    setIO("cbarn2");

    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    ll r[N];
    for (int i = 0; i < N; i++) cin >> r[i];

    // here we talk abt 0 indexed doors btw

    // minimum walking distance to satisfy range [l, r] using k doors
    // if l > r, then it means that we go from r to N - 1 and then from 0 to l
    // dp[l][r][k]
    ll dp[N][N][K];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) dp[i][j][k] = 1e18;
        }
    }

    ll best = 1e18;
    for (int i = 0; i < N; i++) {
        ll dist = 0;

        ll len = 0;
        for (int j = i; ; j = (j + 1) % N) {
            dist += r[j] * len++;
            dp[i][j][0] = min(dp[i][j][0], dist);
            if ((i + N - 1) % N == j) {
                best = min(best, dp[i][j][0]);
                break;
            }
        }
    }

    for (int k = 1; k < K; k++) {
        for (int i = 0; i < N; i++) {
            ll dist = 0;
            ll len = 0;
            for (int j = i; j != (i + N - 1) % N; j = (j + 1) % N) {
                dist += r[j] * len++;
                for (int l = (j + 1) % N; l != i; l = (l + 1) % N) {
                    dp[i][l][k] = min(dp[i][l][k], dp[(j + 1) % N][l][k - 1] + dist);
                    
                    if ((i + N - 1) % N == l) best = min(best, dp[i][l][k]);
                }
            }
        }
    }

    cout << best;
}