// Problem link here:

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T; while (T--) {
        int N, M; cin >> N >> M;

        ll G[N][M];
        bool above[N][M];
        vector<array<ll, 3>> todo;
        for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
            cin >> G[i][j];
            todo.push_back({G[i][j], i, j});
            above[i][j] = false;
        }

        sort(todo.begin(), todo.end(), [](array<ll, 3> one, array<ll, 3> two) {
            return one[0] > two[0];
        });

        int cnt = 0;
        DSU dsu(N * M);

        int best = 0;
        int idx = -1;
        for (auto [Gi, i, j] : todo) {
            cnt++;
            idx++;
            above[i][j] = true;

            if (i > 0 && above[i - 1][j]) {
                if (!dsu.connected(i*M + j, (i-1)*M + j)) cnt--;
                dsu.unite(i*M + j, (i-1)*M + j);
            } if (i < N - 1 && above[i + 1][j]) {
                if (!dsu.connected(i*M + j, (i+1)*M + j)) cnt--;
                dsu.unite(i*M + j, (i+1)*M + j);
            }

            if (j > 0 && above[i][j - 1]) {
                if (!dsu.connected(i*M + j, i*M + j-1)) cnt--;
                dsu.unite(i*M + j, i*M + j-1);
            } if (j < M - 1 && above[i][j + 1]) {
                if (!dsu.connected(i*M + j, i*M + j+1)) cnt--;
                dsu.unite(i*M + j, i*M + j+1);
            }

            // cout << i << " " << j << " " << Gi << " " << cnt << endl;

            if (idx == N*M - 1 || todo[idx + 1][0] != Gi) best = max(best, cnt);
        }

        cout << best << endl;
    }
}