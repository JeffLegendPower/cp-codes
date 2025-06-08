// https://codeforces.com/contest/1466/problem/F

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


struct vct {
    int idx;
    int x, y;
};

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vct> vcts(N);
    for (int i = 0; i < N; i++) {
        vcts[i].idx = i;
        int k;
        cin >> k;
        if (k == 1) {
            cin >> vcts[i].x;
            vcts[i].x--;
            vcts[i].y = M;
        } else {
            cin >> vcts[i].x >> vcts[i].y;
            vcts[i].x--;
            vcts[i].y--;
        }
    }

    DSU dsu(M + 1);
    vector<int> used;
    for (vct cur : vcts) {
        if (dsu.connected(cur.x, cur.y)) continue;
        dsu.unite(cur.x, cur.y);
        used.push_back(cur.idx + 1);
    }

    ll MOD = 1e9 + 7;
    ll T = 1;
    for (int i = 0; i < used.size(); i++) {
        T = (T * 2) % MOD;
    }

    cout << T << " " << used.size() << endl;
    for (int i = 0; i < used.size(); i++) cout << used[i] << " ";
}