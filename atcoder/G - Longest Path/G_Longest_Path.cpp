// https://atcoder.jp/contests/dp/tasks/dp_g

// We can solve this by performing dfs over each connected component of the graph
// For each vertex we save the longest path we can go from that vertex (dynamic programming)
// This makes it so we only need to search each node once
// As the second time we search a node we can just get the memoized longest path length instead of
// recursing over the graph again

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


struct node {
    vector<int> next;
    int longestpath = -1;
};

vector<node> graph;

// DFS through the graph, storing the longest path for each vertex so we only have to check them once
int dfs(int curIdx) {
    if (graph[curIdx].longestpath >= 0) return graph[curIdx].longestpath;
    int longestpath = 0;

    for (int next : graph[curIdx].next) {
        longestpath = max(longestpath, 1 + dfs(next));
    }

    graph[curIdx].longestpath = longestpath;
    return longestpath;
}

int main() {
    int N, M;
    cin >> N >> M;

    // Create the graph
    for (int i = 0; i < N; i++) graph.push_back({});

    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        graph[x - 1].next.push_back(y - 1);
    }

    // DFS through each vertex and store the longest path
    int longestpath = 0;
    for (int i = 0; i < N; i++) {
        longestpath = max(longestpath, dfs(i));
    }

    cout << longestpath;
}