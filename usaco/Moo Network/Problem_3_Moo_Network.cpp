// https://usaco.org/index.php?page=viewproblem2&cpid=1211

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
    ll dist;
    int u, v;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    pll cows[N];
    set<plli> cows1[11];
    set<plli, greater<plli>> cows2[11];

    for (int i = 0; i < N; i++) {
        cin >> cows[i].first >> cows[i].second;
        cows1[cows[i].second].insert({cows[i].first, i});
        cows2[cows[i].second].insert({cows[i].first, i});
    }

    vector<edge> edges;
    for (int i = 0; i < N; i++) {
        ll xi = cows[i].first;
        ll yi = cows[i].second;

        for (int y = 0; y <= 10; y++) {
            auto itr1 = cows1[y].upper_bound({xi, 0});
            auto itr2 = cows2[y].upper_bound({xi, 0});

            if (itr1 != cows1[y].end()) {
                edges.push_back({
                    (itr1->first - xi) * (itr1->first - xi) + (y - yi) * (y - yi),
                    i, itr1->second
                });
            } if (itr2 != cows2[y].end()) {
                edges.push_back({
                    (itr2->first - xi) * (itr2->first - xi) + (y - yi) * (y - yi),
                    i, itr2->second
                });
            }
        }
    }

    sort(edges.begin(), edges.end(), [](edge one, edge two) {
        return one.dist < two.dist;
    });
    
    DSU dsu(N);
    ll mindist = 0;
    for (edge cur : edges) {
        if (dsu.connected(cur.u, cur.v)) continue;
        dsu.unite(cur.u, cur.v);
        mindist += cur.dist;
    }

    cout << mindist << endl;
}