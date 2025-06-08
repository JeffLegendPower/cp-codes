// https://cses.fi/problemset/task/1195

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

struct node {
    vector<plli> next;
    bool searched = false;

    vector<ll> dists;
};
node graph[100000];

void dijkstra(int v) {
    for (int i = 0; i < 100000; i++) graph[i].searched = false;

    priority_queue<plli, vector<plli>, greater<plli>> todo;
    todo.push({0, v});

    while (!todo.empty()) {
        auto [dist, u] = todo.top();
        todo.pop();

        if (graph[u].searched) continue;
        graph[u].searched = true;
        graph[u].dists.push_back(dist);

        for (plli next : graph[u].next) todo.push({dist + next.first, next.second});
    }
}

int main() {
    int N, M; cin >> N >> M;

    vector<array<ll, 3>> edges;
    for (int i = 0; i < M; i++) {
        int u, v;
        ll w; cin >> u >> v >> w;
        u--, v--;
        edges.push_back({u, v, w});

        graph[v].next.push_back({w, u});
    }
    dijkstra(N - 1);

    for (int i = 0; i < N; i++) graph[i].next.clear();
    for (int i = 0; i < M; i++) {
        auto [u, v, w] = edges[i];
        graph[u].next.push_back({w, v});
    }
    dijkstra(0);

    ll best = graph[0].dists[0];

    for (int i = 0; i < N; i++) {
        ll dist = 1e18;
        if (graph[i].dists.size() < 2) continue; // if can't go from 1 to i and from i to N then theres no path here

        for (auto [w, u] : graph[i].next) {
            dist = min(dist, graph[u].dists[0] + (w / 2));
        }

        best = min(best, dist + graph[i].dists[1]);
    }

    cout << best;
}