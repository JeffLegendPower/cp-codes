// https://cses.fi/problemset/task/1673

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
    ll dist = 1e18;
    vector<plli> next;
    vector<int> prev;
    bool can1 = false; // Does a path exist from 1 to this
    bool canN = false; // Does a path exist from this to N
};

vector<node> graph;

void dfs1(int curIdx) {
    graph[curIdx].can1 = true;
    for (plli next : graph[curIdx].next) {
        if (!graph[next.second].can1) dfs1(next.second);
    }
} void dfsN(int curIdx) {
    graph[curIdx].canN = true;
    for (int next : graph[curIdx].prev) {
        if (!graph[next].canN) dfsN(next);
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) graph.push_back({});
    for (int i = 0; i < M; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        graph[a - 1].next.push_back({-c, b - 1});
        graph[b - 1].prev.push_back(a - 1);
    }

    graph[0].dist = 0;

    for (int i = 0; i < N - 1; i++) {
        for (plli edge : graph[i].next) {
            graph[edge.second].dist = min(graph[edge.second].dist, graph[i].dist + edge.first);
            // cout << edge.second << " " << edge.first << " " << i << " " << graph[i].dist << endl;
        }
    }

    dfs1(0);
    dfsN(N - 1);

    // for (int i = 0; i < N; i++) cout << graph[i].can1 << " " << graph[i].canN << " " << graph[i].dist << endl;

    bool positivecycle = false;
    for (int i = 0; i < N; i++) {
        if (!graph[i].can1 || !graph[i].canN) continue;
        for (plli edge : graph[i].next) {
            // Since the weights are negated we still need to check for <
            // because we are actually looking for a negative cycle
            if (graph[i].dist + edge.first < graph[edge.second].dist) {
                positivecycle = true;
                break;
            }
        }
    }

    // cout << graph[N - 1].dist << endl;

    cout << (positivecycle ? -1 : -graph[N - 1].dist) << endl;
}