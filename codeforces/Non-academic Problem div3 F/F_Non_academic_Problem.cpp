// https://codeforces.com/contest/1986/problem/F

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
ll N;  // array size
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
    int tin;
    int low;
    int children = 1;
    
    bool searched = false;
    vector<int> next;
};
vector<node> graph;

int timer = 0;
ll best;

void bridge(int from, int to) {
    ll one = graph[to].children;
    ll two = N - graph[to].children;

    ll cur = one * (one - 1) / 2 + two * (two - 1) / 2;
    best = min(best, cur);
}

int dfs(int curIdx, int parent) {
    graph[curIdx].searched = true;
    graph[curIdx].low = graph[curIdx].tin = timer++;

    for (int next : graph[curIdx].next) {
        if (next == parent) continue;
        if (graph[next].searched) {
            graph[curIdx].low = min(graph[curIdx].low, graph[next].tin);
            continue;
        }

        graph[curIdx].children += dfs(next, curIdx);
        graph[curIdx].low = min(graph[curIdx].low, graph[next].low);

        if (graph[next].low > graph[curIdx].tin) bridge(curIdx, next);
    }
    
    return graph[curIdx].children;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int M;
        cin >> N >> M;
        best = N * (N - 1) / 2;
        
        graph.clear();
        timer = 0;

        for (int i = 0; i < N; i++)
            graph.push_back({});
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            graph[u - 1].next.push_back(v - 1);
            graph[v - 1].next.push_back(u - 1);
        }

        graph[0].tin = 0;

        dfs(0, -1);
        cout << best << endl;
    }
}