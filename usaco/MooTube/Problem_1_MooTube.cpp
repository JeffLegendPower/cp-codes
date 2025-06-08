// https://usaco.org/index.php?page=viewproblem2&cpid=789

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
    ll w;
}; struct qry {
    ll k;
    int v;
    int idx;
    int ans;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("mootube");

    int N, Q;
    cin >> N >> Q;

    vector<edge> edges;
    for (int i = 0; i < N - 1; i++) {
        edge cur;
        cin >> cur.u >> cur.v >> cur.w;
        cur.u--;
        cur.v--;
        edges.push_back(cur);
    }

    sort(edges.begin(), edges.end(), [](edge one, edge two) {
        return one.w > two.w;
    });

    vector<qry> queries;
    for (int i = 0; i < Q; i++) {
        qry cur;
        cin >> cur.k >> cur.v;
        cur.v--;
        cur.idx = i;
        queries.push_back(cur);
    }

    sort(queries.begin(), queries.end(), [](qry one, qry two) {
        return one.k > two.k;
    });

    int edgeidx = 0;
    DSU dsu(N);
    for (int i = 0; i < Q; i++) {
        while (edgeidx < N - 1 && edges[edgeidx].w >= queries[i].k) {
            dsu.unite(edges[edgeidx].u, edges[edgeidx].v);
            edgeidx++;
        }

        queries[i].ans = dsu.sizes[dsu.find(queries[i].v)] - 1;
    }

    sort(queries.begin(), queries.end(), [](qry one, qry two) {
        return one.idx < two.idx;
    });

    for (int i = 0; i < Q; i++) {
        cout << queries[i].ans;
        if (i < Q - 1) cout << endl;
    }
}