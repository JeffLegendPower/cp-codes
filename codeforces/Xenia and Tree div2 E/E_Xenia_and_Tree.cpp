// https://codeforces.com/problemset/problem/342/E

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


struct CentroidDecomp {
	vector<set<int>> tree; // it's not vector<vector<int>>!
	vector<int> parent;
	vector<int> sub;

    vector<vector<int>> forward;

	CentroidDecomp(vector<set<int>> &tree) : tree(tree) {
		int n = tree.size();
		parent.resize(n);
		sub.resize(n);
        forward.resize(n);
		build(0, -1);

        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                forward[parent[i]].push_back(i);
            }
        }
	}

	void build(int u, int p) {
		int n = dfs(u, p); // find the size of each subtree
		int centroid = dfs(u, p, n); // find the centroid
		parent[centroid] = p;

		vector<int> neighbors(tree[centroid].begin(), tree[centroid].end());
		
		// for each tree resulting from the removal of the centroid
		for (auto v : neighbors) {
			tree[centroid].erase(v), // remove the edge to disconnect
			tree[v].erase(centroid), // the component from the tree
			build(v, centroid);
	    }
	}

	int dfs(int u, int p) {
		sub[u] = 1;

		for (auto v : tree[u])
			if (v != p) sub[u] += dfs(v, u);

		return sub[u];
	}

	int dfs(int u, int p, int n) {
		for (auto v : tree[u])
			if (v != p and sub[v] > n/2) return dfs(v, u, n);

		return u;
	}

	int operator[](int i) {
		return parent[i];
	}

    vector<vector<int>> getFoward() {
        return forward;
    } vector<int> getBackward() {
        return parent;
    }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<set<int>> graph(N);
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    CentroidDecomp centroid(graph);
    vector<int> p = centroid.getBackward();


    vector<int> dist(N, 1e6);
    int v = 0;
    dist[v] = 0;

    int k = 0;
    int d = 0;
    while (p[v] != -1) {
        d++;
        if (d < dist[p[v]]) {
            dist[p[v]] = d;
        }
        cout << dist[v] << " "  << v << " " << p[v] << endl;
        v = p[v];
    }

    while (Q--) {
        int t;
        cin >> t >> v;
        v--;

        if (t == 1) {
            dist[v] = 0;
            d = 0;
            while (p[v] != -1) {
                d++;
                dist[p[v]] = min(dist[p[v]], d);
                v = p[v];
            }
        } else if (t == 2) {
            int mindist = dist[v];
            v = p[v];
            int up = 0;

            while (v != -1) {
                up++;
                if (dist[v]+up < mindist) {
                    mindist = dist[v]+up;
                }
                // cout << dist[v] << " " << v << endl;
                v = p[v];

                up++;
            }

            cout << mindist << endl;
        }
    }
}