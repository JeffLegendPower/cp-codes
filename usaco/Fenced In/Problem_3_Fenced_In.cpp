// https://usaco.org/index.php?page=viewproblem2&cpid=623

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

struct gate {
    int cost;
    int a, b;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("fencedin");

    ll A, B;
    int N, M;
    cin >> A >> B >> N >> M;

    ll vert[N + 2], hor[M + 2];
    vert[0] = 0, hor[0] = 0;
    vert[N + 1] = A, hor[M + 1] = B;
    for (int i = 1; i <= N; i++) cin >> vert[i];
    for (int i = 1; i <= M; i++) cin >> hor[i];
    sort(vert, vert + (N + 2));
    sort(hor, hor + (M + 2));

    DSU dsu((N + 1) * (M + 1));
    vector<gate> gates;

    for (int i = 0; i <= N; i++) { // moves from left to right between the verticals
        for (int j = 0; j <= M; j++) { // moves from up to down between the horizontals
            int idx = (M + 1) * i + j;
            
            // if (i > 0) gates.push_back({hor[j + 1] - hor[j], idx, (M + 1) * (i - 1) + j});
            if (i < N) gates.push_back({hor[j + 1] - hor[j], idx, (M + 1) * (i + 1) + j});
            // if (j > 0) gates.push_back({vert[i + 1] - vert[i], idx, (M + 1) * i + j - 1});
            if (j < M) gates.push_back({vert[i + 1] - vert[i], idx, (M + 1) * i + j + 1});
        }
    }

    ll fences = 0;
    sort(gates.begin(), gates.end(), [](gate one, gate two) {
        return one.cost < two.cost;
    });

    for (gate cur : gates) {
        if (dsu.connected(cur.a, cur.b)) continue;
        dsu.unite(cur.a, cur.b);
        fences += cur.cost;
    }

    cout << fences << endl;
}