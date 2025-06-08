// https://atcoder.jp/contests/dp/tasks/dp_v

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

ll M;
struct node {
    vector<int> next;
    // dpf is num ways for the subtree, dpg is num ways for outside of the subtree
    ll dpf, dpg;
};
node graph[100000];

void dfs(int cur, int parent) {
    graph[cur].dpf = 1;
    for (int next : graph[cur].next) {
        if (next == parent) continue;
        dfs(next, cur);
        graph[cur].dpf = (graph[cur].dpf * (1 + graph[next].dpf)) % M;
    }
} void dfs2(int cur, int parent) {
    int children = 0;
    vector<int> childs;
    for (int next : graph[cur].next) {
        if (next == parent) continue;
        children++;
        childs.push_back(next);
    }

    ll pre[children + 1], suff[children + 1];
    pre[0] = 1;
    suff[children] = 1;

    for (int i = 0; i < children; i++) {
        int next = childs[i];
        pre[i + 1] = (pre[i] * (1 + graph[next].dpf)) % M;
    }
    for (int i = children - 1; i >= 0; i--) {
        int next = childs[i];
        suff[i] = (suff[i + 1] * (1 + graph[next].dpf)) % M;
    }

    for (int i = 0; i < children; i++) {
        int next = childs[i];
        ll ways = (pre[i] * suff[i + 1]) % M;
        ways = (ways * (graph[cur].dpg + 1)) % M;
        graph[next].dpg = ways;
    }

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        dfs2(next, cur);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }
    dfs(0, -1);
    dfs2(0, -1);

    for (int i = 0; i < N; i++) cout << ((graph[i].dpf * (graph[i].dpg + 1)) % M) << endl;
}