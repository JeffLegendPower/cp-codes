// https://codeforces.com/contest/1344/problem/B

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    char grid[N][M];
    bool predown[N][M], preup[N][M], preright[N][M], preleft[N][M];
    bool south[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
            south[i][j] = false;
        }
    } 
    
    for (int j = 0; j < M; j++) {
        bool black = false, white = false;
        for (int i = 0; i < N; i++) {
            if (grid[i][j] == '#') black = true;
            if (black && grid[i][j] == '.') white = true;

            predown[i][j] = !white;
        }
    } for (int j = 0; j < M; j++) {
        bool black = false, white = false;
        for (int i = N - 1; i >= 0; i--) {
            if (grid[i][j] == '#') black = true;
            if (black && grid[i][j] == '.') white = true;

            preup[i][j] = !white;
        }
    } for (int i = 0; i < N; i++) {
        bool black = false, white = false;
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '#') black = true;
            if (black && grid[i][j] == '.') white = true;

            preright[i][j] = !white;
        }
    } for (int i = 0; i < N; i++) {
        bool black = false, white = false;
        for (int j = M - 1; j >= 0; j--) {
            if (grid[i][j] == '#') black = true;
            if (black && grid[i][j] == '.') white = true;

            preleft[i][j] = !white;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) south[i][j] = preup[i][j] & predown[i][j] & preright[i][j] & preleft[i][j];
    }

    bool incol = true, inrow = true;
    for (int i = 0; i < N; i++) {
        bool row = false;
        for (int j = 0; j < M; j++) row |= south[i][j];
        if (!row) inrow = false;
    } for (int j = 0; j < M; j++) {
        bool col = false;
        for (int i = 0; i < N; i++) col |= south[i][j];
        if (!col) incol = false;
    }

    if (!incol || !inrow) {
        cout << -1 << endl;
        return 0;
    }

    DSU dsu(N * M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '.') continue;
            if (i > 0 && grid[i - 1][j] == '#') {
                dsu.unite(M * i + j, M * (i - 1) + j);
            }
            // if (i < N - 1 && grid[i + 1][j] == '#') dsu.unite(M * i + j, M * (i + 1) + j);
            if (j > 0 && grid[i][j - 1] == '#') {
                dsu.unite(M * i + j, M * i + (j - 1));
            }
            // if (j < M - 1 && grid[i][j + 1] == '#') dsu.unite(M * i + j, M * i + (j + 1));
        }
    }

    set<int> groups;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '.') continue;
            groups.insert(dsu.find(M * i + j));
        }
    }

    cout << groups.size() << endl;
}