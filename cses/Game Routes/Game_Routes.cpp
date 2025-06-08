// https://cses.fi/problemset/task/1681

// If this was an array where we needed to find the number of paths
// that reach the end, and each element could transition forward to some other elements
// We would use dp, as we could find the number of paths to reach element i, and for each element
// after that that element i could transition to, we would add the number of paths to reach element i to that
// However, this is a graph. But, if we use topological sort, we can sort the vertices in such a way that
// all the edges (if any) of each vertex are directed to vertices after it in the
// topologically sorted graph. This means that we can use our array dp to find the number of ways to reach vertex N
// This will run in O(V) time, taking O(V_i) time to handle the transitions from the i'th vertex, V_i is the number of edges
// going out from the i'th vertex

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
    vector<int> next;
    ll ways = 0;
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

    ll MOD = 1e9 + 7;

    for (int i = 0; i < N; i++) graph.push_back({});
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].next.push_back(b - 1);
    }

    for (int i = 0; i < N; i++) if (!graph[i].searched) toposort(i);
    reverse(sorted.begin(), sorted.end());

    graph[0].ways = 1;
    for (int i : sorted) {
        for (int next : graph[i].next) graph[next].ways = (graph[next].ways + graph[i].ways) % MOD;
    }

    cout << graph[N - 1].ways;
}