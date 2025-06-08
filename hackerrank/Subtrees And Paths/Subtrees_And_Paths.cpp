// https://www.hackerrank.com/challenges/subtrees-and-paths/problem

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


template <class T, class K>
class LazySegtree {
private:
    int N;  // array size
    int h;
    vector<T> t;
    vector<K> d;

    // k is the length of the segment
    T calc(T a, T b, K d, int k) {
        return max(a, b) + d;
    }

    // Update d[p]
    // k is the length of segment
    void apply(int p, K value, int k) {
        // Update t[p] as if it was already affected by d[p]
        t[p] += value;
        if (p < N) d[p] += value;
    }

public:
    LazySegtree(int size) : N(size), h(sizeof(int) * 8 - __builtin_clz(N)), t(2 * size, T()), d(size) {}

    void build(int l, int r) {
        int k = 2;
        for (l += N, r += N-1; l > 1; k <<= 1) {
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; --i) t[i] = calc(t[i<<1], t[i<<1|1], d[i], k);
        }
    }

    void push(int l, int r) {
        int s = h, k = 1 << (h-1);
        for (l += N, r += N-1; s > 0; --s, k >>= 1) for (int i = l >> s; i <= r >> s; ++i) if (d[i] != 0) {
            apply(i<<1, d[i], k);
            apply(i<<1|1, d[i], k);
            d[i] = 0;
        }
    }

    void modify(int l, int r, K value) {
        if (value == 0) return;
        push(l, l + 1);
        push(r - 1, r);
        int l0 = l, r0 = r, k = 1;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l&1) apply(l++, value, k);
            if (r&1) apply(--r, value, k);
        }
        build(l0, l0 + 1);
        build(r0 - 1, r0);
    }

    T query(int l, int r) {
        push(l, l + 1);
        push(r - 1, r);
        T res = -1e18;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = calc(res, t[l++], 0, -1);
            if (r&1) res = calc(res, t[--r], 0, -1);
        }
        return res;
    }
};

template <class T, int V>
class HeavyLight {
    int parent[V], heavy[V], depth[V];
    int root[V], treePos[V], subtree[V];
    LazySegtree<T, T> tree;

    template <class G>
    int dfs(const G& graph, int v) {
        int size = 1, maxSubtree = 0;
        heavy[v] = -1;
        for (int u : graph[v]) if (u != parent[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            int subtree = dfs(graph, u);
            if (subtree > maxSubtree) heavy[v] = u, maxSubtree = subtree;
            size += subtree;
        }
        subtree[v] = size;
        return size;
    }

    template <class G>
    void dfs2(const G& graph, int v, int& i) {
        treePos[v] = i++;
        if (heavy[v] != -1) dfs2(graph, heavy[v], i);
        for (int u : graph[v]) if (u != parent[v] && u != heavy[v]) dfs2(graph, u, i);
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
                for (int j = i; j != -1; j = heavy[j])
                    root[j] = i;

        int k = 0;
        dfs2(graph, 0, k);
    }

    void set(int v, const T& value) {
        tree.modify(treePos[v], value);
    }

    // Need lazy segtree for this one
    void modifyPath(int u, int v, const T& value) {
        processPath(u, v, [this, &value](int l, int r) { tree.modify(l, r, value); });
    }

    void modifySubtree(int v, const T& value) {
        tree.modify(treePos[v], treePos[v] + subtree[v], value);
    }

    void querySubtree(int v, const T& value) {
        return tree.query(treePos[v], treePos[v] + subtree[v]);
    }

    T queryPath(int u, int v) {
        T res = -1e18;
        processPath(u, v, [this, &res](int l, int r) { 
            // Combine
            res = max(res, tree.query(l, r));
        });
        return res;
    }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;
    
    vector<vector<int>> graph(N);
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    HeavyLight<ll, 100000> hld(graph);

    int Q; cin >> Q;
    while (Q--) {
        string s; cin >> s;
        if (s == "add") {
            int t;
            ll val;
            cin >> t >> val;
            t--;
            hld.modifySubtree(t, val);
        } else if (s == "max") {
            int a, b; cin >> a >> b;
            a--, b--;
            cout << hld.queryPath(a, b) << endl;
        }
    }
}