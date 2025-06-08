// https://cses.fi/problemset/task/1197

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
    bool searched = false;
};

struct edge {
    int a, b;
    ll c;
};

vector<node> graph;
vector<edge> edges;

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) graph.push_back({});

    for (int i = 0; i < M; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        graph[a - 1].next.push_back({c, b - 1});
        edges.push_back({a - 1, b - 1, c});
    }

    graph[0].dist = 0;
    // for (int i2 = 0; i2 < N - 1; i2++) {
    //     int i = order[i2];
    for (int i = 0; i < N - 1; i++) {
        for (edge edge : edges) {
            graph[edge.b].dist = min(graph[edge.b].dist, graph[edge.a].dist + edge.c);
        }
        
        cout << graph[4].dist << endl;
    }

    vector<int> negs;

    // for (plli edge : graph[order.back()].next) {
    //     if (graph[order.back()].dist + edge.first < graph[edge.second].dist) negcycle = true;
    // }

    cout << graph[5].dist << " " << graph[4].dist << endl;

    for (edge edge : edges) {
        if (graph[edge.a].dist + edge.c < graph[edge.b].dist) {
            negs.push_back(edge.a);
            negs.push_back(edge.b);
            graph[edge.b].dist = graph[edge.a].dist + edge.c;
            break;
        }
    }

    if (negs.size() == 0) {
        cout << "NO";
        return 0;
    }

    // cout << graph[2].dist << endl;
    int t = 0;
    while (negs.back() != negs[0]) {
        if (t++ > 10) break;
        for (plli edge : graph[negs.back()].next) {
            if (graph[negs.back()].dist + edge.first < graph[edge.second].dist) {
                cout << negs.back() << " " << edge.second << endl;
                graph[edge.second].dist = graph[negs.back()].dist + edge.first;
                negs.push_back(edge.second);
                break;
            }
        }
    }

    cout << "YES" << endl;
    for (int vertex : negs) cout << vertex + 1 << " ";

    // cout << negcycle << endl;
}