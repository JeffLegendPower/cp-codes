// https://codeforces.com/problemset/problem/1528/A

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

    ll l, r;
    ll dpl, dpr;
};
node graph[100000];

void dfs(int cur, int parent) {
    ll l = graph[cur].l, r = graph[cur].r;
    ll dpl = 0, dpr = 0;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        dfs(next, cur);

        dpl += max(graph[next].dpr + abs(l - graph[next].r), graph[next].dpl + abs(l - graph[next].l));
        dpr += max(graph[next].dpr + abs(r - graph[next].r), graph[next].dpl + abs(r - graph[next].l));
    }

    graph[cur].dpl = dpl, graph[cur].dpr = dpr;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        for (int i = 0; i < N; i++) {
            graph[i].next.clear();
            cin >> graph[i].l >> graph[i].r;
        }

        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        }

        dfs(0, -1);

        cout << max(graph[0].dpl, graph[0].dpr) << endl;
    }
}