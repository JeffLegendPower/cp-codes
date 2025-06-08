// https://codeforces.com/problemset/problem/1929/D

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

ll MOD = 998244353;

struct node {
    vector<int> next;
    bool searched = false;

    // dpi, number of subtrees such that there are at most i bad intersections from the current vertex v to 
    // some other vertex in the subtree (so leaves pretty much but that doesn't matter)
    ll dp0 = 0, dp1 = 0, dp2 = 0;
};
vector<node> graph;

void dfs(int cur, int p) {
    graph[cur].dp0 = 1; // always 1 way to have 0 bad intersection paths... have no intersections be bad
    graph[cur].dp1 = 1;
    graph[cur].dp2 = 0;

    bool leaf = true;
    for (int next : graph[cur].next) {
        if (next == p) continue;
        leaf = false;
        dfs(next, cur);

        graph[cur].dp1 *= graph[next].dp1 + 1;
        graph[cur].dp1 %= MOD;

        graph[cur].dp2 += graph[next].dp2;
        graph[cur].dp2 += graph[next].dp1; // If current vertex is bad then only one child can have a bad path from it to its subtree

        graph[cur].dp2 %= MOD;
    }
    
    graph[cur].dp1 = (graph[cur].dp1 + MOD - 1) % MOD;

    graph[cur].dp1 += graph[cur].dp0; // 0 bad intersection paths but if we set the current vertex to be bad
    graph[cur].dp1 %= MOD;

}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        graph.clear();

        for (int i = 0; i < N; i++) graph.push_back({});
        for (int i = 0; i < N - 1; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        }

        dfs(0, -1);
        cout << ((graph[0].dp0 + graph[0].dp1 + graph[0].dp2) % MOD) << endl;
    }
}