// https://cses.fi/problemset/task/1135

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
const int Nmax = 8e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return min(a, b);
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 1e6;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end

struct node {
    vector<int> next;
    int height;
    int touridx;
};
node graph[200000];

int euler[400000];
int timer = 0;

void euler_tour(int cur, int parent, int height) {
    graph[cur].height = height;
    graph[cur].touridx = timer;
    euler[timer++] = cur;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur, height + 1);
        euler[timer++] = cur;
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, Q;
    cin >> n >> Q;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }
    euler_tour(0, -1, 0);

    N = timer;
    for (int i = 0; i < timer; i++) {
        t[N + i] = graph[euler[i]].height;
    }
    build();

    while (Q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        int eulera = graph[a].touridx, eulerb = graph[b].touridx;
        int ha = graph[a].height, hb = graph[b].height;

        int hp = query(min(eulera, eulerb), max(eulera, eulerb) + 1);

        cout << (ha + hb - 2*hp) << endl;
    }
}