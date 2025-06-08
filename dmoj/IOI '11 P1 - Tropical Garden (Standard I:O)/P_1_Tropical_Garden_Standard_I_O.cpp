// https://dmoj.ca/problem/ioi11p1io

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

struct node {
    vector<pii> edges;
    ll mostw = -1;

    pii next;
    vector<int> back;

    int time[2] = {-1, -1};
};
vector<node> graph;

void dfs(int v, int time, int num, bool root) {
    if (!root) graph[v].time[num] = time;

    for (int x : graph[v].back) {
        if (graph[x].time[num] != -1) continue;
        dfs(x, time+1, num, false);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M, P;
    cin >> N >> M >> P;

    for (int i = 0; i < 2*N; i++) {
        graph.push_back({});
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].edges.push_back({i, v});
        graph[v].edges.push_back({i, u});
    }

    for (int i = 0; i < N; i++) {
        sort(graph[i].edges.begin(), graph[i].edges.end());

        graph[i].next = graph[i].edges[0];
        graph[i].mostw = graph[i].edges[0].first;
        graph[N+i].mostw = graph[i].edges[0].first;

        if (graph[i].edges.size() > 1) graph[N+i].next = graph[i].edges[1];
        else graph[N+i].next = graph[i].edges[0];
    }

    for (int i = 0; i < 2*N; i++) {
        auto [w, x] = graph[i].next;
        if (graph[x].mostw == w) graph[i].next.second += N;

        graph[graph[i].next.second].back.push_back(i);
    }

    dfs(P, 0, 0, true);
    dfs(P+N, 0, 1, true);

    int Q; cin >> Q;
    while (Q--) {
        ll K; cin >> K;

        int cnt = 0;
        for (int i = 0; i < N; i++) {
            bool possible = false;
            ll dist = graph[i].time[0];
            ll cycle = graph[P].time[0];
            if (dist == K) possible = true;
            if (cycle != -1 && dist == (K % cycle)) possible = true;

            dist = graph[i].time[1];
            cycle = graph[P+N].time[1];
            if (dist == K) possible = true;
            if (cycle != -1 && dist == (K % cycle)) possible = true;

            cnt += possible;
        }

        cout << cnt << " ";
    }
}

// #include <bits/stdc++.h>
// #include <vector>
// // #include "garden.h"
// // #include "gardenlib.h"

// using namespace std;

// // void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
// // {
// int main() {
//     int N, M, P; cin >> N >> M >> P;
//     int R[M][2];
//     for (int i = 0; i < M; i++) cin >> R[i][0] >> R[i][1];
//     int Q; cin >> Q;
//     int G[Q]; for (int i = 0; i < Q; i++) cin >> G[i];

//         vector<int> ans(Q);
//         vector<vector<int>> g(N, vector<int>(0));
//         for (int i = 0; i < M; i++)
//         {
//                 g[R[i][0]].push_back(R[i][1]);
//                 g[R[i][1]].push_back(R[i][0]);
//         }

//         vector<vector<int>> DP(N, vector<int>(2, -1));

//         int timer = -1;
//         int cycSz = -1;
//         auto dfs = [&](auto self, int node, int prevNode) -> void
//         {
//                 timer++;
//                 int state = 0, nextNode = g[node][0];
//                 if (g[node][0] == prevNode && g[node].size() >= 2)
//                 {
//                         state = 1;
//                         nextNode = g[node][1];
//                 }
//                 if (DP[node][state] != -1)
//                 {
//                         if (node == P) cycSz = timer-DP[node][state];
//                         return;
//                 }
//                 DP[node][state] = timer;
//                 self(self, nextNode, node);
//                 return;
//         };

//         dfs(dfs, P, (g[P].size()>1?-1:g[P][0]));
//         DP.clear();
//         DP.resize(N, vector<int>(2, -2));
//         DP[P][0] = 0;

//         auto prop = [&](auto self, int node, int prevNode) -> int {
//                 int state = 0, nextNode = g[node][0];
//                 if (g[node][0] == prevNode && g[node].size() >= 2)
//                 {
//                         state = 1;
//                         nextNode = g[node][1];
//                 }
//                 if (DP[node][state] != -2) return DP[node][state];
//                 DP[node][state] = -1;
//                 int step = self(self, nextNode, node);
//                 if (step != -1) step++;
//                 DP[node][state] = step;
//                 return DP[node][state];
//         };
//         for (int i = 0; i < N; i++) prop(prop, i, -1);
                

//         int cnt = 0;
//         // auto dfs2 = [&](auto self, int node, int prevNode, int K) -> void
//         // {
//         //         int state = 0;
//         //         if (g[node][0] != prevNode) state = 1;
//         //         if (state == 0 && DP[node][state] != -1) {
//         //                 if (DP[node][state] == K || (cycSz != -1 && K > DP[node][state] && (K-DP[node][state])%cycSz == 0)) cnt++;
//         //         }
//         //         // cout << "node " << node << " " << state << '\n';
//         //         if (vis[node][state] != -1) return;
//         //         vis[node][state] = 1;
//         //         if (state == 0) {
//         //                 for (int i = 1; i < g[node].size(); i++) self(self, g[node][i], node, K);
//         //         } else self(self, g[node][0], node, K);
//         //         return;
//         // };
//         for (int i = 0; i < Q; i++) {
//                 cnt = 0;
//                 // vis.clear();
//                 // vis.resize(N, vector<int>(2, -1));
//                 // dfs2(dfs2, P, g[P][0], G[i]);
//                 for (int j = 0; j < N; j++) {
//                         if (DP[j][0] == G[i] || (DP[j][0] != -1 && cycSz != -1 && G[i] > DP[j][0] && (G[i]-DP[j][0])%cycSz == 0)) cnt++;
//                 }
//                 ans[i] += cnt;
//         }

//         if (g[P].size() > 1) {
//                 DP.clear();
//                 DP.resize(N, vector<int>(2, -1));
//                 timer = 1; cycSz = -1;
//                 dfs(dfs, P, g[P][0]);
//                 DP.clear();
//                 DP.resize(N, vector<int>(2, -2));
//                 DP[P][1] = 0;
//                 for (int i = 0; i < N; i++) {
//                         prop(prop, i, -1);
//                 }
//                 for (int i = 0; i < Q; i++) {
//                         cnt = 0;
//                         // vis.clear();
//                         // vis.resize(N, vector<int>(2, -1));
//                         // dfs2(dfs2, P, -1, G[i]);
//                         for (int j = 0; j < N; j++) {
//                                 if (DP[j][0] == G[i] || ( DP[j][0] != -1 && cycSz != -1 && G[i] > DP[j][0] && (G[i]-DP[j][0])%cycSz == 0)) cnt++;
//                         }
//                         ans[i] += cnt;
//                 }
//         }

//         for (int i = 0; i < Q; i++) cout << ans[i] << " ";
// }
