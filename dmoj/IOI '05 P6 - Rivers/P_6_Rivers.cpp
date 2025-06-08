// https://dmoj.ca/problem/ioi05p6

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



const int MAXN = 101;
const int MAXK = 51;

struct node {
    ll w, p, d;
    vector<pii> next;

    vector<ll> dists;
    int depth;
};
vector<node> graph;

void dfs(int v, int depth) {
    graph[v].depth = depth;
    for (auto [x, w] : graph[v].next) {
        for (int i = 0; i < depth; i++) {
            graph[x].dists.push_back(graph[v].dists[i] + w);
        }
        graph[x].dists.push_back(w);

        dfs(x, depth+1);
    }
}

ll dp1[MAXN][MAXK+1], dp2[MAXN][MAXK+1][MAXN];

void dfs2(int v) {
    int depth = graph[v].depth;
    bool leaf = graph[v].next.empty();

    if (leaf) {
        for (int k = 0; k <= MAXK; k++) {
            if (k > 0) dp1[v][k] = 0;
            else dp1[v][k] = 2e9;
            for (int j = 0; j < depth; j++) dp2[v][k][j] = min(dp1[v][k], graph[v].w*graph[v].dists[j]);
        }
        return;
    }

    int children = graph[v].next.size();

    ll dppre[MAXK+1];
    ll dppre2[MAXK+1][depth];
    for (int i = 0; i <= MAXK; i++) {
        dppre[i] = 0;
        for (int j = 0; j < depth; j++) dppre2[i][j] = 0;
    }

    for (auto [x, w] : graph[v].next) {
        dfs2(x);

        for (int i = MAXK; i >= 0; i--) {
            ll minn = 2e9;
            for (int j = 0; j <= i; j++) minn = min(minn, dppre[i-j] + dp2[x][j][depth]);
            dppre[i] = minn;
        }

        for (int d = 0; d < depth; d++) {
            for (int i = MAXK; i >= 0; i--) {
                ll minn = 2e9;
                for (int j = 0; j <= i; j++) minn = min(minn, dppre2[i-j][d] + dp2[x][j][d]);
                dppre2[i][d] = minn;
            }
        }
    }

    for (int k = 0; k <= MAXK; k++) {
        if (k > 0) dp1[v][k] = dppre[k-1];
        else dp1[v][k] = 2e9;
        for (int j = 0; j < depth; j++) dp2[v][k][j] = min(dp1[v][k], graph[v].w*graph[v].dists[j] + dppre2[k][j]);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    graph.resize(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> graph[i].w >> graph[i].p >> graph[i].d;
        graph[graph[i].p].next.push_back({i, graph[i].d});
    }

    dfs(0, 0);
    dfs2(0);

    cout << dp1[0][K+1];
}