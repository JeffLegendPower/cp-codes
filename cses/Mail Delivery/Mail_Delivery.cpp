// https://cses.fi/problemset/task/1691

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


struct node {
    vector<int> next;
};

node graph[100000];
vector<array<int, 3>> edges;

vector<int> eulerpath;
void dfs(int x) {
    while (graph[x].next.size()) {
        int i = graph[x].next.back();
        graph[x].next.pop_back();

        if (edges[i][2]) continue;
        edges[i][2] = true;

        int v = edges[i][0] == x ? edges[i][1] : edges[i][0];
        dfs(v);
    }

    eulerpath.push_back(x);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M; cin >> N >> M;

    bool works = true;
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        edges.push_back({u, v, false});

        graph[u].next.push_back(i);
        graph[v].next.push_back(i);
    }
    for (int i = 0; i < N; i++) if (graph[i].next.size()&1) works = false;

    dfs(0);

    if (eulerpath.size() < M + 1) works = false;
    reverse(eulerpath.begin(), eulerpath.end());

    if (!works) cout << "IMPOSSIBLE";
    else for (int v : eulerpath) cout << v + 1 << " ";
}