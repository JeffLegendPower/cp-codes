// https://vjudge.net/contest/693462#problem/A

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


class DSU {
  public:
    vector<int> parents;
    vector<int> sizes;
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

    int N, M;
    cin >> N >> M;

    vector<array<int, 3>> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--;
        edges[i][1]--;
    }

    sort(edges.begin(), edges.end(), [](array<int, 3>& one, array<int, 3>& two) {
        return one[2] < two[2];
    });

    DSU dsu(N);
    int totalcost = 0;
    for (int i = 0; i < M;) {
        int w = edges[i][2];
        int j = i;

        int cost = 0;
        for (; j <= M; j++) {
            if (j == M || edges[j][2] != w) break;
            if (!dsu.connected(edges[j][0], edges[j][1])) cost++;
        }

        while (i < j) {
            if (!dsu.connected(edges[i][0], edges[i][1])) {
                dsu.unite(edges[i][0], edges[i][1]);
                cost--;
            }
            i++;
        }

        totalcost += cost;
    }

    cout << totalcost;
}