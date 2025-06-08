// https://atcoder.jp/contests/dp/tasks/dp_p

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

ll MOD = 1e9 + 7;

struct node {
    vector<int> next;
    ll dp[2]; // 0: black, 1: white
};
node graph[100000];

void dfs(int cur, int parent) {
    graph[cur].dp[0] = 1;
    graph[cur].dp[1] = 1;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        dfs(next, cur);

        graph[cur].dp[0] = (graph[cur].dp[0] * (graph[next].dp[1])) % MOD;
        graph[cur].dp[1] = (graph[cur].dp[1] * (graph[next].dp[0] + graph[next].dp[1])) % MOD;
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }

    dfs(0, -1);
    cout << ((graph[0].dp[0] + graph[0].dp[1]) % MOD);
}