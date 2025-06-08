// https://codeforces.com/contest/1817/problem/B

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
};
vector<node> graph;

void bfs(int N, int root, vector<pii> &edges) {
    int sizze = 1e6;

    for (int end : graph[root].next) {
        // cur vertex, dist
        deque<pii> todo;
        vector<int> from(N, -1);
        todo.push_back({root, 0});
        int enddist = 1e6;

        for (int i = 0; i < N; i++) graph[i].searched = false;

        while (!todo.empty()) {
            auto [cur, dist] = todo.front();
            todo.pop_front();
            if (cur == end) enddist = dist;

            for (int next : graph[cur].next) {
                if (graph[next].searched) continue;
                if (cur == root && next == end) continue;
                todo.push_back({next, dist + 1});
                graph[next].searched = true;
                from[next] = cur;
            }
        }

        if (enddist < sizze) {
            edges.clear();
            edges.push_back({root, end});
            for (int i = end; i != root; i = from[i]) edges.push_back({i, from[i]});
            int added = 0;
            int other = edges.back().first;
            for (int next : graph[root].next) {
                if (added == 2) break;
                if (next == end || next == other) continue;
                added++;
                edges.push_back({root, next});
            }
        }
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;
    int T2 = T;

    while (T--) {
        int N, M;
        cin >> N >> M;
        graph.clear();

        for (int i = 0; i < N; i++) graph.push_back({});
        vector<pii> edges2;
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            graph[u - 1].next.push_back(v - 1);
            graph[v - 1].next.push_back(u - 1);
            edges2.push_back({u, v});
        }

        bool fish = false;
        vector<pii> edges;
        for (int i = 0; i < N; i++) {
            if (graph[i].next.size() >= 4) {
                bfs(N, i, edges);
            }
        }

        if (edges.size() == 0) {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;
        cout << edges.size() << endl;
        for (pii edge : edges) cout << edge.first + 1 << " " << edge.second + 1 << endl;
    }
}