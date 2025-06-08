// https://cses.fi/problemset/task/1669

// This problem is asking us to find a cycle of atleast 3 vertices in a graph
// We can do this by dfs'ing through each of the components of the graph
// if we ever run into an already searched vertex that's not the previous vertex,
// then we've found a cycle

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
    int from = -1;
};

vector<node> graph;

int pivot = -1;

void dfs(int curIdx, int last) {
    if (pivot != -1) return;

    // cout << curIdx << " " << last << endl;
    // for (int next : graph[curIdx].next) cout << next << " ";
    // cout << endl;

    graph[curIdx].searched = true;
    graph[curIdx].from = last;

    for (int next : graph[curIdx].next) {
        if (pivot != -1) return;
        if (graph[next].searched) {
            if (next == last) continue;
            graph[next].from = curIdx;
            pivot = next;
            return;
        }
        else dfs(next, curIdx);
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) graph.push_back({});

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;

        graph[a - 1].next.push_back(b - 1);
        graph[b - 1].next.push_back(a - 1);
    }

    for (int i = 0; i < N; i++) if (!graph[i].searched && pivot == -1) dfs(i, -1);

    if (pivot == -1) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<int> backtrack;
    backtrack.push_back(pivot + 1);
    for (int i = graph[pivot].from; i != pivot; i = graph[i].from) {
        backtrack.push_back(i + 1);
    }
    backtrack.push_back(pivot + 1);

    cout << backtrack.size() << endl;
    for (int i : backtrack) cout << i << " ";
}