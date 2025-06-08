// https://usaco.org/index.php?page=viewproblem2&cpid=946

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
    ll val;
    int u, v;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("walk");

    int N, K;
    cin >> N >> K;

    int idx = 0;
    edge edges[N * (N - 1) / 2];
    for (ll i = 0; i < N; i++) {
        for (ll j = i + 1; j < N; j++) {
            edges[idx++] = {
                (2019201913ll * (i + 1) + 2019201949ll * (j + 1)) % 2019201997ll, 
                i, j
            };
        }
    }

    sort(edges, edges + (N * (N - 1) / 2), [](edge one, edge two) {
        return one.val < two.val;
    });

    // for a valid division, there must be exactly k connected components
    // but if we have >k connected components we can still create a valid divison from that so thats not an issue
    // and if we sort the edges in increasing order, in order to get an M greater than the current edge weight
    // the 2 vertices in that edge must be in the same connected component, so we can just unite them

    ll best = 0;
    int components = N;
    DSU dsu(N);

    for (edge cur : edges) {
        if (dsu.connected(cur.u, cur.v)) continue;

        best = cur.val;
        dsu.unite(cur.u, cur.v);
        components--;
        if (components < K) break;
    }
    
    cout << best;
}