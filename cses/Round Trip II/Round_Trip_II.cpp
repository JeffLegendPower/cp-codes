// https://cses.fi/problemset/task/1678

// We just need to find a cycle in the directed graph given
// This can be done in O(n) by searching each vertex once
// When we run our dfs, we will maintain a recursion stack and the parent of each node
// And when recursing back up remove the parent for a node in the recursion stack
// So now if we find a node which has a parent (or the starting node in our dfs), then we have a cycle
// and can backtrack to record it

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
    int color = 0;
    vector<int> next;
};

vector<node> graph;
vector<int> recursionstack;

vector<int> cycle;
bool found = false;
int dfs(int curIdx) {
    if (found) return -1;
    graph[curIdx].searched = true;

    for (int next : graph[curIdx].next) {
        if (found) return -1;

        if (recursionstack[next] != -1) {
            cycle.push_back(next + 1);
            cycle.push_back(curIdx + 1);
            return next;
        } if (graph[next].searched) continue;

        recursionstack[next] = curIdx;
        int response = dfs(next);
        recursionstack[next] = -1;
        if (response == curIdx) {
            found = true;
            cycle.push_back(curIdx + 1);
            return -1;
        } else if (response != -1) {
            cycle.push_back(curIdx + 1);
            return response;
        }
    }

    return -1;
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        graph.push_back({});
        recursionstack.push_back(-1);
    } for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a - 1].next.push_back(b - 1);
    }

    for (int i = 0; i < N; i++) {
        if (graph[i].searched == 0 && !found) {
            recursionstack[i] = -2;
            dfs(i);
            recursionstack[i] = -1;
        }
    }

    if (!found) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    cout << cycle.size() << endl;
    reverse(cycle.begin(), cycle.end());
    for (int vertex : cycle) cout << vertex << " ";
}