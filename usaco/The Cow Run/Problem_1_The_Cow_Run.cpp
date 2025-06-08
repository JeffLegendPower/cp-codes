// https://usaco.org/index.php?page=viewproblem2&cpid=265

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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("cowrun");

    ll N;
    cin >> N;

    ll cows[N];
    for (int i = 0; i < N; i++) cin >> cows[i];

    sort(cows, cows + N);

    // min damage d across subsegment [l, r], with FJ ending at left or right cow of the subsegment k
    // k=0 if at left, k=1 if at right
    // dp[l][r][k] = d
    ll dp[N][N][2];

    for (int len = 1; len <= N; len++) {
        for (int l = 0; l <= N - len; l++) {
            if (len == 1) {
                dp[l][l][0] = N * abs(cows[l]);
                dp[l][l][1] = N * abs(cows[l]);
                continue;
            }

            dp[l][l + len - 1][1] = min(
                dp[l][l + len - 2][1] + (N - len + 1) * abs(cows[l + len - 1] - cows[l + len - 2]),
                dp[l][l + len - 2][0] + (N - len + 1) * abs(cows[l + len - 1] - cows[l])
            );

            dp[l][l + len - 1][0] = min(
                dp[l + 1][l + len - 1][1] + (N - len + 1) * abs(cows[l + len - 1] - cows[l]),
                dp[l + 1][l + len - 1][0] + (N - len + 1) * abs(cows[l + 1] - cows[l])
            );
        }
    }

    cout << min(dp[0][N - 1][0], dp[0][N - 1][1]);
}