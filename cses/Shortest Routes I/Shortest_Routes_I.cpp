// https://cses.fi/problemset/task/1671

// This problem is dijkstra implementation
// We will start at vertex 1 and run dijkstra to go to each
// vertex and calculate the minimum distance
// Since we're using a priority queue, the time complexity is O((V + E)*logV)

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
    ll dist;
    vector<plli> next;
};

vector<node> graph;

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) graph.push_back({});

    for (int i = 0; i < M; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        graph[a - 1].next.push_back({c, b - 1});
    }

    // Dijkstra's
    priority_queue<plli, vector<plli>, greater<plli>> next;
    next.push({0, 0});

    while (!next.empty()) {
        plli cur = next.top();
        next.pop();

        if (graph[cur.second].searched) continue;
        graph[cur.second].searched = true;

        graph[cur.second].dist = cur.first;

        for (plli edge : graph[cur.second].next) {
            if (graph[edge.second].searched) continue;
            next.push({cur.first + edge.first, edge.second});
        }
    }

    for (int i = 0; i < N; i++) cout << graph[i].dist << " ";
}