// https://zibada.guru/gcj/ks2021a/problems/#D

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
    int u, v;
    ll w;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    int T2 = 1;

    while (T--) {
        int N;

        cin >> N;

        int A[N][N];
        ll B[N][N];

        int R[N], C[N];

        // vertices are rows and columns
        // {row, column}
        vector<edge> edges;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cin >> A[i][j];
        } for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cin >> B[i][j];
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) if (A[i][j] == -1) edges.push_back({i, j, B[i][j]});
        }

        for (int i = 0; i < N; i++) cin >> R[i];
        for (int i = 0; i < N; i++) cin >> C[i];

        // when the graph is tree-like, it means that we have leaves and the leaves only have 1 unknown value, which we can 
        // calculate with the checksums. However, when it's not tree-like (has 1 or more cycles) we will need to break the cycle
        // by having Grace find the value of one edge (unknown val) in the cycle. This edge obviously must be the lowest weight edge
        // and thats essentially the same as picking every other maximally weighted edge, which is esentially finding the
        // maximum spanning tree (actually forest) of the graph
        sort(edges.begin(), edges.end(), [](edge one, edge two) {
            return one.w > two.w;
        });

        DSU dsu(2*N);
        ll hours = 0;
        for (edge cur : edges) {
            hours += cur.w;
            if (dsu.connected(cur.u, N + cur.v)) continue;

            dsu.unite(cur.u, N + cur.v);
            hours -= cur.w;
        }

        cout << "Case #" << T2++ << ": " << hours << endl;
    }
}