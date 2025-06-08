// https://cses.fi/problemset/task/1680

// I was immidiately thinking dp when I saw this
// Set the distance for vertex 1 to be 1 (can't be 0 because we are including vertex 1 in the distance)
// And for each vertex, we can iterate over the edges
// and set the distance of the vertex to be the max of its current distance and
// the distance of the previous vertex + 1. However, I didn't know how to order my dp
// so the transitions would work. But, by using topological sort, we can create an
// ordering of the vertices such that it is guaranteed that no vertex ordered before the
// current one has a dp state dependent on it
// So vertex 1 would be first, then the vertex after vertex 1, and so on
// If a vertex never had its dp state updated by the time we reach it (set to -1),
// then that means it's in a seperate component than the component
// with vertex 1 so it won't help in calculating distance as we can't reach it or any of it's
// next vertices from vertex 1
// With topological sort and dp, this runs in O(n)

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
    bool searched = false;
    int dist = -1;
    int last = -1;
};
vector<node> graph;
vector<int> sorted;

void toposort(int curIdx) {
    graph[curIdx].searched = true;
    for (int next : graph[curIdx].next) if (!graph[next].searched) toposort(next);
    sorted.push_back(curIdx);
}

int main() {
    int N, M;
    cin >> N >> M;
    
    for (int i = 0; i < N; i++) graph.push_back({});

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].next.push_back(b - 1);
    }

    for (int i = 0; i < N; i++) if (!graph[i].searched) toposort(i);
    reverse(sorted.begin(), sorted.end());

    graph[0].dist = 1;
    for (int i2 = 0; i2 < N; i2++) {
        int i = sorted[i2];
        if (graph[i].dist == -1) {
            continue;
        } for (int next : graph[i].next) {
            if (graph[i].dist + 1 > graph[next].dist) {
                graph[next].dist = graph[i].dist + 1;
                graph[next].last = i;
            }
        }
    }

    if (graph[N - 1].dist == -1) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<int> path;
    for (int i = N - 1; i != 0; i = graph[i].last) {
        path.push_back(i + 1);
    }
    path.push_back(1);
    reverse(path.begin(), path.end());

    cout << graph[N - 1].dist << endl;
    for (int vertex : path) cout << vertex << " ";

}