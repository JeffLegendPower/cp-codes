// https://usaco.org/index.php?page=viewproblem2&cpid=576

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

struct node {
    vector<int> next;
    int start = 0, end = 0;
};
vector<node> graph;

int jmp[20][50000], dep[50000];

void dfs(int v, int p) {
    for (int x : graph[v].next) {
        if (x == p) continue;
        jmp[0][x] = v, dep[x] = dep[v] + 1;
        dfs(x, v);
    }
}

int kth(int i, int k) { // kth ancestor of i
    for(int x=19; x>=0; x--)
        if(k & 1<<x) i = jmp[x][i];
    return i;
}


int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    // cout << dep[a] << " " << dep[b] << endl;
    a = kth(a, dep[a] - dep[b]);
    if(a == b) return a;
    for(int x = 19; x >= 0; x--)
        if(jmp[x][a] != jmp[x][b])
        a = jmp[x][a], b = jmp[x][b];
    return jmp[0][a];
}

int best = 0;
int dfs2(int v, int p) {
    int summ = 0;
    for (int x : graph[v].next) {
        if (x == p) continue;
        summ += dfs2(x, v);
    }

    best = max(best, summ + graph[v].start - graph[v].end / 2);
    return summ + graph[v].start - graph[v].end;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("maxflow");

    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; i++) graph.push_back({});
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }

    dfs(0, -1);
    for(int i = 1; i < 20; i++)
        for(int j = 0; j < N; j++)
            jmp[i][j] = jmp[i-1][jmp[i-1][j]];

    while (K--) {
        int u, v; cin >> u >> v;
        u--, v--;

        int p = lca(u, v);

        graph[u].start++;
        graph[v].start++;
        graph[p].end += 2;
    }

    dfs2(0, -1);

    cout << best;
}