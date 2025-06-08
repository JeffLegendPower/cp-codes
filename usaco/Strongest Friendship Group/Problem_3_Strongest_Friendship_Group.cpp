// https://usaco.org/index.php?page=viewproblem2&cpid=1259

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

  public:
    vector<int> sizes;
	DSU(int size) : parents(size), sizes(size, 1) {
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
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};

struct edge {
    int u, v;
    ll frnds;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // {degree, vertex idx}
    vector<pii> vertices(N);
    for (int i = 0; i < N; i++) vertices[i] = {0, i};
    vector<vector<int>> next(N);

    vector<edge> edges;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        vertices[u].first++, vertices[v].first++;
        next[u].push_back(v);
        next[v].push_back(u);
        edges.push_back({u, v});
    }

    set<pii> verts;
    for (int i = 0; i < N; i++) verts.insert(vertices[i]);
    vector<int> rem;

    int cnt = 0;
    while (verts.size() > 0) {
        pii todo = *verts.begin();
        verts.erase(todo);
        rem.push_back(todo.second);

        vertices[todo.second].first = 0;

        for (int nexti : next[todo.second]) {
            if (verts.find(vertices[nexti]) == verts.end()) continue;
            verts.erase(vertices[nexti]);
            vertices[nexti].first--;
            verts.insert(vertices[nexti]);
            cnt++;
        }
    }

    reverse(rem.begin(), rem.end());

    ll str = 0;
    DSU dsu(N);
    vector<bool> inuse(N, false);
    for (int node : rem) {
        inuse[node] = true;
        for (int nexti : next[node]) {
            if (!inuse[nexti]) continue;
            dsu.unite(node, nexti);
            vertices[node].first++;
            vertices[nexti].first++;
        }

        str = max(str, (ll) vertices[node].first * dsu.sizes[dsu.find(node)]);
    }

    cout << str;
}