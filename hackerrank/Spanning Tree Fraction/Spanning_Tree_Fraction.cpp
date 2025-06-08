// https://www.hackerrank.com/contests/w31/challenges/spanning-tree-fraction/problem

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

// Segtree end
struct edge {
    int u, v;
    double a, b;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<edge> edges;
    for (int i = 0; i < M; i++) {
        edge cur;
        cin >> cur.u >> cur.v >> cur.a >> cur.b;
        edges.push_back(cur);
    }

    double low = 0, high = 100 * N;
    pll frac;
    for (int itr = 0; itr < 60; itr++) {
        double mid = low + (high - low) / 2;

        sort(edges.begin(), edges.end(), [mid](edge one, edge two) {
            return (one.a - one.b * mid) > (two.a - two.b * mid);
        });

        DSU dsu(N);
        double score = 0;
        ll suma = 0, sumb = 0;
        for (edge cur : edges) {
            if (dsu.connected(cur.u, cur.v)) continue;
            dsu.unite(cur.u, cur.v);
            score += cur.a - cur.b * mid;
            suma += cur.a;
            sumb += cur.b;
        }

        if (score >= 0) {
            frac = {suma, sumb};
            low = mid;
        } else high = mid;
    }

    ll gcdd = gcd(frac.first, frac.second);
    frac.first /= gcdd;
    frac.second /= gcdd;

    cout << frac.first << "/" << frac.second;
}