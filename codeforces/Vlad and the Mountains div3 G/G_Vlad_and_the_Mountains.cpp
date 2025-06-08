// https://codeforces.com/contest/1851/problem/G

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
	int find(int x) {
		return parents[x] == x ? x : (parents[x] = find(parents[x]));
	}

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

struct qry {
    ll a, b;
    ll e;
    int idx;
    bool possible;

    ll energy;
}; struct node {
    ll height;
    vector<int> next;
};
vector<node> graph;

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        graph.clear();

        // {height, idx}
        vector<plli> heights;
        for (int i = 0; i < N; i++) {
            node cur;
            cin >> cur.height;
            graph.push_back(cur);
            heights.push_back({cur.height, i});
        }
        sort(heights.begin(), heights.end());

        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            graph[u - 1].next.push_back(v - 1);
            graph[v - 1].next.push_back(u - 1);
        }

        int Q;
        cin >> Q;

        qry queries[Q];
        for (int i = 0; i < Q; i++) {
            cin >> queries[i].a >> queries[i].b >> queries[i].e;
            queries[i].a--;
            queries[i].b--;

            queries[i].energy = queries[i].e + graph[queries[i].a].height;
            queries[i].idx = i;
        }

        sort(queries, queries + Q, [](qry one, qry two) {
            return one.energy < two.energy;
        });

        int left = 0;
        DSU dsu(N);

        for (int q = 0; q < Q; q++) {
            ll energy = queries[q].energy;

            while (left < N && heights[left].first <= energy) {
                for (int next : graph[heights[left].second].next) {
                    if (graph[next].height <= energy) dsu.unite(heights[left].second, next);
                }
                left++;
            }

            queries[q].possible = dsu.connected(queries[q].a, queries[q].b);
        }

        sort(queries, queries + Q, [](qry one, qry two) {
            return one.idx < two.idx;
        });

        for (int i = 0; i < Q; i++) cout << (queries[i].possible ? "YES" : "NO") << endl;
        cout << endl;
    }
}