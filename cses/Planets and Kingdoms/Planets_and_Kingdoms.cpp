// https://cses.fi/problemset/task/1683

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
    vector<int> next, prev;
    bool searched = false;
    
    int group = 0;
};
node graph[100000];

vector<int> topo;
void toposort(int x) {
    graph[x].searched = true;
    for (int v : graph[x].next) if (!graph[v].searched) toposort(v);
    topo.push_back(x);
}

void dfs(int x, int g) {
    graph[x].searched = true;
    graph[x].group = g;
    for (int v : graph[x].prev) if (!graph[v].searched) dfs(v, g);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M; cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].prev.push_back(u);
    }
    for (int i = 0; i < N; i++) if (!graph[i].searched) toposort(i);
    for (int i = 0; i < N; i++) graph[i].searched = false;
    reverse(topo.begin(), topo.end());

    int g = 0;
    for (int i : topo) {
        if (graph[i].searched) continue;
        g++;
        dfs(i, g);
    }

    cout << g << endl;
    for (int i = 0; i < N; i++) cout << graph[i].group << " ";
}