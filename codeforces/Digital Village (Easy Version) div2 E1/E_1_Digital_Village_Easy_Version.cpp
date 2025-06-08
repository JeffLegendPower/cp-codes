// https://codeforces.com/contest/2021/problem/E1

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
    vector<ll> num;
    vector<ll> latency;
	DSU(int size) : parents(size), sizes(size, 1), num(size, 0), latency(size, 0) {
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
        num[x_root] += num[y_root];
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M, P;
        cin >> N >> M >> P;

        DSU dsu(N);
        for (int i = 0; i < P; i++) {
            int s;
            cin >> s;
            dsu.num[s - 1] = 1;
        }
        vector<ll> edges[M];
        for (int i = 0; i < M; i++) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            u--, v--;
            edges[i] = {u, v, w};
        }
        sort(edges, edges + M, [](vector<ll> one, vector<ll> two) {
            return one[2] < two[2];
        });

        int num = P;
        vector<ll> latency(N, 1e18);
        for (int i = P - 1; i < N; i++) latency[i] = 0;

        ll c = 0;

        for (vector<ll> edge : edges) {
            int u = edge[0], v = edge[1];
            ll w = edge[2];

            int pu = dsu.find(u), pv = dsu.find(v);
            if (pu == pv) continue;

            ll lu = dsu.latency[pu], lv = dsu.latency[pv];
            ll nu = dsu.num[pu], nv = dsu.num[pv];

            ll l = min(lu + nv*w, lv + nu*w);

            c += l - lu - lv;

            if (dsu.num[pu] && dsu.num[pv]) num--;

            dsu.unite(u, v);
            dsu.latency[dsu.find(u)] = l;

            latency[num - 1] = min(latency[num - 1], c);
        }
        
        for (int i = 0; i < N; i++) cout << latency[i] << " ";
        cout << endl;
    }
}