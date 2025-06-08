// https://codeforces.com/contest/1387/problem/B1

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
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

    int end;
    bool moved;
};
node graph[100000];
ll total = 0;

void dfs(int cur, int parent) {
    for (int next : graph[cur].next) {
        if (next == parent) continue;

        dfs(next, cur);
    }

    if (graph[cur].moved || cur == 0) return;
    graph[cur].moved = true;
    graph[parent].moved = true;
    swap(graph[cur].end, graph[parent].end);
    total += 2;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) graph[i].end = i;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }

    dfs(0, -1);
    if (!graph[0].moved) {
        int child = graph[0].next[0];
        graph[0].moved = true;
        graph[child].moved = true;
        swap(graph[0].end, graph[child].end);
        total += 2;
    }

    cout << total << endl;
    for (int i = 0; i < N; i++) cout << graph[i].end + 1 << " ";
}