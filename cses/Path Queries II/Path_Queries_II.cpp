// https://cses.fi/problemset/task/2134

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

template <class T>
class Segtree {
private:
    int N;  // array size
    vector<T> t;

    T combine(T a, T b) {
        return max(a, b);
    }

public:
    Segtree(int size) : N(size), t(2 * size, T()) {}

    void build() {  // Build the tree
        for (int i = N - 1; i > 0; i--) 
            t[i] = combine(t[i<<1], t[i<<1|1]);
    }

    void modify(int p, T value) {  // Set value at position p
        for (t[p += N] = value; p > 1; p >>= 1) 
            t[p >> 1] = combine(t[p], t[p^1]);
    }

    T query(int l, int r) {  // Query on interval [l, r)
        T res = T();
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = combine(res, t[l++]);
            if (r&1) res = combine(res, t[--r]);
        }
        return res;
    }
};

template <class T, int V>
class HeavyLight {
    int parent[V], heavy[V], depth[V];
    int root[V], treePos[V];
    Segtree<T> tree;

    template <class G>
    int dfs(const G& graph, int v) {
        int size = 1, maxSubtree = 0;
        for (int u : graph[v]) if (u != parent[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            int subtree = dfs(graph, u);
            if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
            size += subtree;
        }
        return size;
    }

    template <class BinaryOperation>
    void processPath(int u, int v, BinaryOperation op) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(treePos[root[v]], treePos[v] + 1);
        }
        if (depth[u] > depth[v]) swap(u, v); op(treePos[u], treePos[v] + 1);
    }

public:
    template <class G>
    // Pass in adjacency list vector<vector<int>>
    HeavyLight(const G& graph) : tree(graph.size()) {
        int n = graph.size();
        fill_n(heavy, n, -1);
        parent[0] = -1;
        depth[0] = 0;
        dfs(graph, 0);
        for (int i = 0, currentPos = 0; i < n; ++i)
            if (parent[i] == -1 || heavy[parent[i]] != i)
                for (int j = i; j != -1; j = heavy[j]) {
                    root[j] = i;
                    treePos[j] = currentPos++;
                }
        }

    void set(int v, const T& value) {
        tree.modify(treePos[v], value);
    }

    // Need lazy segtree for this one
    void modifyPath(int u, int v, const T& value) {
        processPath(u, v, [this, &value](int l, int r) { tree.modify(l, r, value); });
    }

    T queryPath(int u, int v) {
        T res = T();
        processPath(u, v, [this, &res](int l, int r) { 
            // Combine
            res = max(res, tree.query(l, r));
        });
        return res;
    }
};

vector<vector<int>> graph;
int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    ll w[N];
    for (int i = 0; i < N; i++) {
        graph.push_back({});
        cin >> w[i];
    }

    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HeavyLight<ll, 200000> hld(graph);

    for (int i = 0; i < N; i++) hld.set(i, w[i]);
    // cout << hld.queryPath(0, 1);

    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int s;
            ll x;
            cin >> s >> x;
            s--;

            hld.set(s, x);
        } else if (t == 2) {
            int a, b;
            cin >> a >> b;
            a--, b--;

            cout << hld.queryPath(a, b) << " ";
        }
    }
}