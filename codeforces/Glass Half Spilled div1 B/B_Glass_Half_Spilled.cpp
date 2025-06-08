// https://codeforces.com/contest/1458/problem/B

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

    cout << fixed << setprecision(10);

    int N;
    cin >> N;

    pii glasses[N];
    double totalwater = 0;
    ll totalspace = 0;
    for (int i = 0; i < N; i++) {
        cin >> glasses[i].first >> glasses[i].second;
        totalspace += glasses[i].first;
        totalwater += glasses[i].second;
    }

    // max (sum b) for subset containing i elements with max size sum of j
    // dp[i][j]
    double dp[N + 1][totalspace + 1];
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < totalspace + 1; j++) dp[i][j] = -1;
    }

    dp[0][0] = 0;
    for (pii glass : glasses) {
        for (int i = N - 1; i >= 0; i--) {
            for (int j = 0; j < totalspace + 1 - glass.first; j++) {
                if (dp[i][j] == -1) continue;
                dp[i + 1][j + glass.first] = max(dp[i + 1][j + glass.first], dp[i][j] + glass.second);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        double best = 0;
        for (int j = 0; j < totalspace + 1; j++) {
            if (dp[i][j] == -1) continue;
            double cur = min((double) j, (totalwater + dp[i][j]) / 2);
            best = max(best, cur);
        }
        cout << best << " ";
    }
}