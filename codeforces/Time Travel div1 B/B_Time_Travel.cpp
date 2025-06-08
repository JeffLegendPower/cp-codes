// https://codeforces.com/contest/1887/problem/B

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
    bool searched = false;
    int mintime = 1e6;
    vector<pii> next; // time, nextidx
}; struct edge {
    int u, v;
    int time;
    bool searched = false;
};
vector<node> graph;
vector<edge> edges;

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, t;
    cin >> N >> t;

    for (int i = 0; i < N; i++) graph.push_back({});
    graph[0].mintime = 0;
    for (int i = 1; i <= t; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            edge cur;
            cin >> cur.u >> cur.v;
            cur.u--;
            cur.v--;
            cur.time = i;

            graph[cur.u].next.push_back({i, cur.v});
            graph[cur.v].next.push_back({i, cur.u});
            edges.push_back(cur);
        }
    }

    int k;
    cin >> k;
    vector<set<int>> idxs(t + 1);

    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        idxs[a].insert(i + 1);
    }

    // time, target vertex
    priority_queue<pii, vector<pii>, greater<pii>> todo;
    for (pii cur : graph[0].next) {
        auto time = idxs[cur.first].upper_bound(0);
        // cout << cur.first << " " << *time << endl;
        if (time == idxs[cur.first].end()) continue;
        todo.push({*time, cur.second});
    }
    graph[0].searched = true;

    while (!todo.empty()) {
        pii cur = todo.top();
        todo.pop();
        if (graph[cur.second].searched) continue;

        graph[cur.second].searched = true;
        graph[cur.second].mintime = min(graph[cur.second].mintime, cur.first);

        for (pii next : graph[cur.second].next) {
            auto time = idxs[next.first].upper_bound(graph[cur.second].mintime);
            if (time == idxs[next.first].end()) continue;
            todo.push({*time, next.second});
        }
    }

    if (graph[N - 1].mintime == 1e6) cout << -1 << endl;
    else cout << graph[N - 1].mintime << endl;
}