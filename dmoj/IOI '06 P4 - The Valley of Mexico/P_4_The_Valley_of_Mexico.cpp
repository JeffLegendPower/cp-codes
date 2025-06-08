// https://dmoj.ca/problem/ioi06p4

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

    int N, M; cin >> N >> M;
    
    bool edges[N][N];
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) edges[i][j] = false;
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        edges[u][v] = true;
        edges[v][u] = true;
        // cout << u << " "  << v << endl;
    }

    // dp[v][len+N] = u
    // v is the current vertex and len is the length of the segment, pos is clockwise and neg is anticlockwise
    // u is the previous vertex (for backtracking)
    array<int, 2> dp[N][2*N + 1];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2*N+1; j++) dp[i][j] = {-1, 0};
        dp[i][1 + N] = {i, 0};
        dp[i][-1 + N] = {i, 0};
    }

    for (int len = 1; len < N; len++) {
        for (int v = 0; v < N; v++) {
            if (edges[v][(v+1)%N] && dp[v][-len + N][0] != -1) {
                dp[(v+1)%N][-len-1 + N] = {v, -len};
            } if (edges[v][(N + v-len)%N] && dp[v][-len + N][0] != -1) {
                dp[(N + v-len)%N][len+1 + N] = {v, -len};
            }

            if (edges[v][(N + v-1)%N] && dp[v][len + N][0] != -1) {
                dp[(N + v-1)%N][len+1 + N] = {v, len};
            } if (edges[v][(v+len)%N] && dp[v][len + N][0] != -1) {
                dp[(v+len)%N][-len-1 + N] = {v, len};
            }
        }
    }

    int t = 0;
    for (int v = 0; v < N; v++) {
        if (dp[v][N + N][0] == -1) continue;

        int len = N;
        while (abs(len) >= 1) {
            cout << v+1 << endl;
            auto [v2, len2] = dp[v][len + N];
            v = v2;
            len = len2;
        }

        return 0;
    }

    for (int v = 0; v < N; v++) {
        if (dp[v][-N + N][0] == -1) continue;

        int len = -N;
        while (abs(len) >= 1) {
            cout << v+1 << endl;
            auto [v2, len2] = dp[v][len + N];
            v = v2;
            len = len2;
        }

        return 0;
    }

    cout << -1;
}