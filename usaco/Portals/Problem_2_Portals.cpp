// https://usaco.org/index.php?page=viewproblem2&cpid=1138

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
    int a, b;
    ll c;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> connections(2*N, -1);

    vector<edge> edges;

    vector<ll> weights;
    for (int i = 0; i < N; i++) {
        ll w;
        cin >> w;
        edges.push_back({i*4 + 1, i*4 + 2, w});
        for (int j = 0; j < 4; j++) {
            int portal;
            cin >> portal;

            if (connections[portal - 1] != -1) {
                edges.push_back({i*4 + j, connections[portal - 1], 0});
            } else connections[portal - 1] = i*4 + j;
            
            if (j % 2 == 1) {
                edges.push_back({i*4 + j, i*4 + j - 1, 0});
            }
        }
    }
    
    sort(edges.begin(), edges.end(), [](edge one, edge two) {
        return one.c < two.c;
    });

    ll cost = 0;
    DSU dsu(4*N);
    for (edge cur : edges) {
        if (dsu.connected(cur.a, cur.b)) continue;
        dsu.unite(cur.a, cur.b);
        cost += cur.c;
    }

    cout << cost << endl;
}