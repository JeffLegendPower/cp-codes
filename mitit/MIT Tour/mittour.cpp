// https://mitit.org/Contest/ViewProblem/mit-tour?cid=advanced2-2025

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

const int MAXN = 2e5;
int jmp[20][MAXN], dep[MAXN];

// add child to parent
void addchild(int p, int v) {
    jmp[0][v] = p;
    dep[v] = dep[p] + 1;
}

// prepare jumps
void build() {
    for (int i = 1; i < 20; i++) for(int j = 0; j < MAXN; j++) jmp[i][j] = jmp[i-1][jmp[i-1][j]];
}

// kth ancestor of i
int kth(int i, int k) {
    for(int x = 19; x >= 0; x--) if (k & (1<<x)) i = jmp[x][i];
    return i;
}

// LCA of a, b
int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    a = kth(a, dep[a] - dep[b]);
    if(a == b) return a;
    for(int x = 19; x >= 0; x--) if(jmp[x][a] != jmp[x][b]) a = jmp[x][a], b = jmp[x][b];
    return jmp[0][a];
}

struct node {
    ll dp = 1e18;
    int dep = 0;
    ll dist = 0;

    vector<plli> next;
};
vector<node> graph;

vector<int> nodes[200000];
int maxdep = 0;
void dfs(int v, int p) {
    nodes[graph[v].dep].push_back(v);
    maxdep = max(maxdep, graph[v].dep);

    for (auto [w, x] : graph[v].next) {
        if (x == p) continue;
        graph[x].dep = graph[v].dep + 1;
        graph[x].dist = graph[v].dist + w;
        addchild(v, x);

        dfs(x, v);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        graph.push_back({});
    }

    for (int i = 0; i < N-1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].next.push_back({w, v});
        graph[v].next.push_back({w, u});
    }

    dfs(0, -1);
    build();

    for (int v : nodes[maxdep]) graph[v].dp = 0;
    for (int dep = maxdep - 1; dep >= 0; dep--) {
        for (int v : nodes[dep]) {
            for (int u : nodes[dep+1]) {
                int p = lca(u, v);
                if (p == v && dep > 0) continue;
                graph[v].dp = min(graph[v].dp, graph[u].dp + graph[v].dist + graph[u].dist - 2*graph[p].dist);
            }
        }
    }

    cout << graph[0].dp;
}