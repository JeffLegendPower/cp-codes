// https://dmoj.ca/problem/ccc21s4

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
const int Nmax = 1e6;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return min(a, b);
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = INT_MAX;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end


struct node {
    int time = 1e6;
    vector<int> prev;
    bool searched = false;
};

vector<node> graph;

void bfs(int start) {
    // index, time
    deque<pii> next;

    next.push_back({start, 0});
    graph[start].searched = true;

    while (!next.empty()) {
        pii cur = next.front();
        next.pop_front();
        graph[cur.first].time = cur.second;

        for (int prev : graph[cur.first].prev) {
            if (graph[prev].searched) continue;
            graph[prev].searched = true;
            next.push_back({prev, cur.second + 1});
        }
    }
}

int main() {
    int W, D;
    cin >> N >> W >> D;

    for (int i = 0; i < N; i++) graph.push_back({});

    for (int i = 0; i < W; i++) {
        int a, b;
        cin >> a >> b;

        graph[b - 1].prev.push_back(a - 1);
    }

    bfs(N - 1);

    int stations[N];

    for (int i = 0; i < N; i++) {
        cin >> stations[i];
        t[N + i] = graph[stations[i] - 1].time + i;
    }

    build();

    while (D--) {
        int a, b;
        cin >> a >> b;


        modify(a - 1, graph[stations[b - 1] - 1].time + a - 1);
        modify(b - 1, graph[stations[a - 1] - 1].time + b - 1);

        swap(stations[a - 1], stations[b - 1]);

        cout << query(0, N) << endl;
    }
}