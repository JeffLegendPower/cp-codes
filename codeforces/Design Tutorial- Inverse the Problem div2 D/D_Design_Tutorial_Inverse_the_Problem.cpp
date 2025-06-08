// https://codeforces.com/contest/472/problem/D

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
    ll w;
    int u, v;
};

struct node {
    vector<plli> next;
};
vector<node> graph;

const int MAXN = 2000;
ll d[MAXN][MAXN], d2[MAXN][MAXN];

void dfs(int curIdx, int parent, int root, ll dist) {
    d2[root][curIdx] = dist;

    for (plli next : graph[curIdx].next) {
        if (next.second == parent) continue;
        dfs(next.second, curIdx, root, dist + next.first);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N;

    vector<edge> edges;
    bool works = true;
    for (int i = 0; i < N; i++) {
        graph.push_back({});
        for (int j = 0; j < N; j++) {
            cin >> d[i][j];
            d2[i][j] = -1;
            if (j > i) {
                edges.push_back({d[i][j], i, j});
                if (d[i][j] == 0) works = false; // we cant have any zero-weight edges
            }
        }
    }

    DSU dsu(N);

    sort(edges.begin(), edges.end(), [](edge one, edge two) {
        return one.w < two.w;
    });

    for (edge cur : edges) {
        if (dsu.connected(cur.u, cur.v)) continue;
        dsu.unite(cur.u, cur.v);
        graph[cur.u].next.push_back({cur.w, cur.v});
        graph[cur.v].next.push_back({cur.w, cur.u});
    }

    for (int i = 0; i < N; i++) dfs(i, -1, i, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) if (d[i][j] != d2[i][j]) works = false;
    }

    cout << (works ? "YES" : "NO") << endl;
}