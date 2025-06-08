// https://dmoj.ca/problem/btoi14p6

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

#define edge array<int, 2>

vector<vector<int>> graph;
vector<edge> edges;
vector<bool> used;
vector<vector<int>> paths;

int other(edge e, int v) {
    if (e[0] == v) return e[1];
    else return e[0];
}

vector<bool> stackk;
void eulercycle(int v) {
    if (stackk[v]) {
        stackk[v] = false;
        paths.push_back({v});
        return;
    }

    while (!graph[v].empty()) {
        int eidx = graph[v].back();
        graph[v].pop_back();
        if (used[eidx]) continue;
        used[eidx] = true;

        stackk[v] = true;
        eulercycle(other(edges[eidx], v));
        if (stackk[v]) {
            stackk[v] = false;
            paths[paths.size()-1].push_back(v);
            break;
        }
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    graph.resize(N);
    stackk.assign(N, false);
    edges.resize(M);
    used.assign(M, false);

    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        edges[i] = {u, v};
        graph[u].push_back(i);
        graph[v].push_back(i);
    }

    for (int i = 0; i < N; i++) eulercycle(i);

    for (int i = 0; i < paths.size(); i++) {
        for (int v : paths[i]) cout << v+1 << " ";
        cout << endl;
    }
}