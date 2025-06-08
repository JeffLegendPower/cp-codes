// https://usaco.org/index.php?page=viewproblem2&cpid=384

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

class DSU {
  private:
	vector<int> parents;

  public:
    vector<int> sizes;
    vector<vector<int>> starts;
	DSU(int size) : parents(size), sizes(size, 1), starts(size) {
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

        for (int start : starts[y_root]) starts[x_root].push_back(start);

		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};

const int MAXN = 500, MAXM = 500;
int N, M, T;
ll h[MAXN][MAXM];
bool start[MAXN][MAXM];

struct strt {
    int i, j;
    int d = -1;
}; struct edge {
    int u, v;
    int d;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("skilevel");
    
    cin >> N >> M >> T;

    vector<strt> starts;
    DSU dsu(N*M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cin >> h[i][j];
    } for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> start[i][j];
            if (start[i][j]) {
                starts.push_back({i, j});
                dsu.starts[i*M + j].push_back(starts.size() - 1);
            }
        }
    }

    if (T == 1) {
        cout << 0;
        return 0;
    }

    vector<edge> edges;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i > 0) edges.push_back({i*M + j, (i - 1)*M + j, abs(h[i][j] - h[i - 1][j])});
            if (j > 0) edges.push_back({i*M + j, i*M + j - 1, abs(h[i][j] - h[i][j - 1])});
        }
    }

    sort(edges.begin(), edges.end(), [](edge &one, edge &two) {
        return one.d < two.d;
    });

    for (edge cur : edges) {
        // cout << cur.d << endl;
        if (dsu.connected(cur.u, cur.v)) continue;
        dsu.unite(cur.u, cur.v);

        int pu = dsu.find(cur.u);
        if (dsu.sizes[pu] < T) continue;

        for (int sidx = dsu.starts[pu].size() - 1; sidx >= 0; sidx--) {
            starts[dsu.starts[pu][sidx]].d = cur.d;
            dsu.starts[pu].pop_back();
        }
        // for (int start : dsu.starts[pu]) {
        //     // cout << start << endl;
        //     if (starts[start].d == -1) starts[start].d = cur.d;
        // }
    }

    ll total = 0;
    for (strt start : starts) total += start.d;
    cout << total;
}