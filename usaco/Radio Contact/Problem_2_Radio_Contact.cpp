// https://usaco.org/index.php?page=viewproblem2&cpid=598

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

ll dist(pll one, pll two) {
    return (one.first - two.first) * (one.first - two.first) + (one.second - two.second) * (one.second - two.second);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("radio");

    int N, M;
    cin >> N >> M;

    pll fpath[N + 1], bpath[M + 1];
    cin >> fpath[0].first >> fpath[0].second >> bpath[0].first >> bpath[0].second;

    string fstr, bstr;
    cin >> fstr >> bstr;

    for (int i = 0; i < N; i++) {
        fpath[i + 1] = fpath[i];
        if (fstr[i] == 'N') fpath[i + 1].second++;
        if (fstr[i] == 'S') fpath[i + 1].second--;
        if (fstr[i] == 'E') fpath[i + 1].first++;
        if (fstr[i] == 'W') fpath[i + 1].first--;
    } for (int i = 0; i < M; i++) {
        bpath[i + 1] = bpath[i];
        if (bstr[i] == 'N') bpath[i + 1].second++;
        if (bstr[i] == 'S') bpath[i + 1].second--;
        if (bstr[i] == 'E') bpath[i + 1].first++;
        if (bstr[i] == 'W') bpath[i + 1].first--;
    }

    ll dp[N + 1][M + 1];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) dp[i][j] = 1e9;
    }

    dp[0][0] = 0;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (i < N) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + dist(fpath[i + 1], bpath[j]));
            if (j < M) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + dist(fpath[i], bpath[j + 1]));

            if (i < N && j < M) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + dist(fpath[i + 1], bpath[j + 1]));
        }
    }

    cout << dp[N][M];
}