// https://usaco.org/index.php?page=viewproblem2&cpid=491&lang=en

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
    ll pcost = 0;
    ll becost = 0;

    vector<int> next;
    bool searched = false;
};
vector<node> graph;

void bfs(int start, ll incr, bool porbe) {
    deque<plli> todo;
    todo.push_back({0, start});
    graph[start].searched = true;
    
    while (!todo.empty()) {
        auto [cost, idx] = todo.front();
        todo.pop_front();
        if (porbe) graph[idx].pcost += cost;
        else graph[idx].becost += cost;

        for (int next : graph[idx].next) {
            if (graph[next].searched) continue;
            graph[next].searched = true;
            todo.push_back({cost + incr, next});
        }
    }    
}

int main() {
    // Comment out for interactive problems
    // ios::sync_with_stdio(false);
	// cin.tie(nullptr);

    freopen("piggyback.in", "r", stdin);
    freopen("piggyback.out", "w", stdout);

    ll B, E, P;
    int N, M;
    cin >> B >> E >> P >> N >> M;

    for (int i = 0; i < N; i++) graph.push_back({});
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].next.push_back(b - 1);
        graph[b - 1].next.push_back(a - 1);
    }

    bfs(0, B, false);
    for (int i = 0; i < N; i++) graph[i].searched = false;
    bfs(1, E, false);
    for (int i = 0; i < N; i++) graph[i].searched = false;
    bfs(N - 1, P, true);

    ll mincost = 1e18;
    for (int i = 0; i < N; i++) {
        mincost = min(mincost, graph[i].pcost + graph[i].becost);
    }

    cout << mincost;
}