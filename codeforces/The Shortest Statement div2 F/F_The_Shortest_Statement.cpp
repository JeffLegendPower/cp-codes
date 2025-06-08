// https://codeforces.com/contest/1051/problem/F

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
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 2e5;  // limit for array size
int N;  // array size
pii t[2 * Nmax];

pii oper(pii a, pii b) {
    return a.second < b.second ? a : b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

int query(int l, int r) {  // on interval [l, r)
  pii res = {-1, 1e6};
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res.first;
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
    ll d;
};

struct node {
    vector<plli> next;
    vector<plli> extra;
    ll dist;

    int time;
    int height;
};
node graph[100000];

int euler[200000];
int timer = 0;
void euler_tour(int cur, int parent, int height, ll dist) {
    graph[cur].dist = dist;

    graph[cur].time = timer;
    graph[cur].height = height;
    euler[timer++] = cur;

    for (auto [d, next] : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur, height + 1, dist + d);
        euler[timer++] = cur;
    }
}

int parent(int u, int v) {
    int utime = graph[u].time, vtime = graph[v].time;
    return query(min(utime, vtime), max(utime, vtime) + 1);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, M;
    cin >> n >> M;

    DSU dsu(n);
    vector<edge> extras;
    for (int i = 0; i < M; i++) {
        edge cur;
        cin >> cur.u >> cur.v >> cur.d;
        cur.u--, cur.v--;

        graph[cur.u].extra.push_back({cur.d, cur.v});
        graph[cur.v].extra.push_back({cur.d, cur.u});

        if (dsu.connected(cur.u, cur.v)) extras.push_back(cur);
        else {
            dsu.unite(cur.u, cur.v);
            graph[cur.u].next.push_back({cur.d, cur.v});
            graph[cur.v].next.push_back({cur.d, cur.u});
        }
    }

    euler_tour(0, -1, 0, 0);

    N = timer;
    for (int i = 0; i < N; i++) t[N + i] = {euler[i], graph[euler[i]].height};
    build();

    ll dists[extras.size()][n];
    for (int i = 0; i < extras.size(); i++) {
        for (int j = 0; j < n; j++) dists[i][j] = 1e18;
        int start = extras[i].u;

        priority_queue<plli, vector<plli>, greater<plli>> pq;
        pq.push({0, start});
        dists[i][start] = 0;
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dists[i][u]) continue;

            for (auto [w, v] : graph[u].extra) {
                if (dists[i][v] < d + w) continue;
                pq.push({d + w, v});
                dists[i][v] = d + w;
            }
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        int utime = graph[u].time, vtime = graph[v].time;
        int p = parent(u, v);

        ll mindist = graph[u].dist + graph[v].dist - 2 * graph[parent(u, v)].dist;
        for (int i = 0; i < extras.size(); i++) {
            mindist = min(mindist, dists[i][u] + dists[i][v]);
        }
        cout << mindist << endl;
    }
}