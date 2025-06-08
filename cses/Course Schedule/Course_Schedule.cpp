// https://cses.fi/problemset/task/1679

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
    int idx;
};
vector<node> graph;
vector<int> recursionstack;
vector<int> sorted;

bool iscyclic(int curIdx) {
    graph[curIdx].searched = true;
    for (int next : graph[curIdx].next) {
        if (recursionstack[next] != -1) {
            return true;
        } if (graph[next].searched) continue;
        recursionstack[next] = curIdx;
        bool res = iscyclic(next);
        recursionstack[next] = -1;
        if (res) return true;
    }

    return false;
}

void dfs(int curIdx) {
    graph[curIdx].searched = true;

    for (int next : graph[curIdx].next) {
        if (!graph[next].searched) dfs(next);
    }
    sorted.push_back(curIdx);
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        node cur;
        cur.idx = i;
        graph.push_back(cur);
        recursionstack.push_back(-1);
    } for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].next.push_back(b - 1);
    }

    bool cyclic = false;
    for (int i = 0; i < N; i++) {
        if (!graph[i].searched) {
            recursionstack[i] = -2;
            cyclic |= iscyclic(i);
            recursionstack[i] = -1;
        }
    }
    
    for (int i = 0; i < N; i++) graph[i].searched = false;

    if (cyclic) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    // Topological sort
    for (int i = 0; i < N; i++) if (!graph[i].searched) dfs(i);
    reverse(sorted.begin(), sorted.end());

    for (int i = 0; i < N; i++) cout << sorted[i] + 1 << " ";
}