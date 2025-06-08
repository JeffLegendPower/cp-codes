// https://usaco.org/index.php?page=viewproblem2&cpid=1042

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

class DSU {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
    vector<vector<int>> nodes;
    vector<int> children;
	DSU(int size) : parents(size), sizes(size, 1), nodes(size), children(size, 0) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	/** @return the "representative" node in x's component */
	int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;

        for (int node : nodes[y_root]) nodes[x_root].push_back(node);
        children[x_root] += children[y_root];
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};

const int NMAX = 2 * 1e5;
vector<int> out[NMAX];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        out[a].push_back(b);
    }

    DSU dsu(N);
    int components = N;

    stack<int> todo;
    for (int i = 0; i < N; i++) {
        dsu.nodes[i].push_back(i);

        dsu.children[i] = out[i].size();
        if (dsu.children[i] > 1) todo.push(i);
    }

    while (!todo.empty()) {
        int cur = todo.top();
        todo.pop();

        int root = out[dsu.nodes[cur][0]][0];
        for (int i = dsu.nodes[cur].size() - 1; i >= 0; i--) {
            for (int j = out[dsu.nodes[cur][i]].size() - 1; j >= 0; j--) {
                int node = out[dsu.nodes[cur][i]][j];
                if (node == root) continue;
                out[dsu.nodes[cur][i]].pop_back();

                if (dsu.connected(root, node)) continue;
                dsu.unite(root, node);
                components--;
            }

            if (i > 0) dsu.nodes[cur].pop_back();
        }
    }
}