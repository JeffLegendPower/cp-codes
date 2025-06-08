// https://codeforces.com/contest/1659/problem/E

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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
    vector<bool> iseven;

  public:
	DSU(int size) : parents(size), sizes(size, 1), iseven(size, false) {
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

        iseven[x_root] = iseven[x_root] | iseven[y_root];
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }

    bool even(int x) { return iseven[find(x)]; }
    void seteven(int x) { iseven[find(x)] = true; }
};

#define all3 array<ll, 3>

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<all3> edges;
    for (int i = 0; i < M; i++) {
        all3 cur; cin >> cur[0] >> cur[1] >> cur[2];
        cur[0]--;
        cur[1]--;
        edges.push_back(cur);
    }

    vector<all3> qs;
    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        qs.push_back({u, v, 2});
    }

    for (int b = 0; b < 30; b++) {
        DSU dsu(N);
        for (all3 e : edges) {
            if (!(e[2]&(1ll<<b))) continue;
            dsu.unite(e[0], e[1]);
        }

        for (int i = 0; i < Q; i++) {
            if (dsu.connected(qs[i][0], qs[i][1])) qs[i][2] = 0ll;
        }
    }

    for (int b = 1; b < 30; b++) {
        DSU dsu(N);
        for (all3 e : edges) {
            if (!(e[2]&1)) {
                dsu.seteven(e[0]);
                dsu.seteven(e[1]);
            }

            if ((e[2]&((1ll<<b) + 1)) != (1ll<<b) + 1) continue;
            dsu.unite(e[0], e[1]);
        }

        for (int i = 0; i < Q; i++) {
            if (dsu.even(qs[i][0])) qs[i][2] = min(qs[i][2], 1ll);
        }
    }

    for (int i = 0; i < Q; i++) cout << qs[i][2] << endl;
}