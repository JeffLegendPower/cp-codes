// https://codeforces.com/contest/2007/problem/E

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
    vector<int> next;
    int parent;

    // how many times the edge with this child was used
    ll numused = 0;

    int todoidx = -1;

    bool searched = false;
};
vector<node> graph;
vector<set<int>> todos;
int curtodo = 0;

void dfs(int curidx) {
    graph[curidx].searched = true;

    bool leaf = true;
    for (int next : graph[curidx].next) {
        if (graph[next].searched) graph[curidx].parent = next;
        else {
            leaf = false;
            if (graph[curidx].todoidx == -1 || todos[graph[next].todoidx].size() > todos[graph[curidx].todoidx].size())
                graph[curidx].todoidx = graph[next].todoidx;
        }

        if (next == curidx + 1) graph[next].numused++;
    }

    if (leaf) {
        todos.push_back({});
        graph[curidx].todoidx = todos.size() - 1;
    }

    for (int next : graph[curidx].next) {
        if (graph[next].searched) continue;
        if (graph[next].todoidx == graph[curidx].todoidx) continue;
        for (auto val : todos[graph[next].todoidx]) todos[graph[curidx].todoidx].insert(val);
    }

    for (auto val : )
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        ll w;
        cin >> N >> w;
        graph.clear();
        todos.clear();

        for (int i = 0; i < N; i++) {
            graph.push_back({});
        }
        for (int i = 0; i < N - 1; i++) {
            int p;
            cin >> p;
            graph[p - 1].next.push_back(i + 1);
        }

        dfs(0);
    }
}