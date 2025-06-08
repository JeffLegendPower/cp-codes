// https://codeforces.com/problemset/problem/1900/E

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
    vector<int> prev;

    bool vis = false;
    int id = -1; // SCC
    
    ll a = 0;

    int num = 0;
    ll total = 1e18;
    int path = -1;
};
vector<node> graph;
vector<node> sccs;
vector<int> ord;

void dfs1(int v) {
    graph[v].vis = true;
    for (int u : graph[v].next) if (!graph[u].vis) dfs1(u);
    ord.push_back(v);
} void dfs2(int v, int comp) {
    graph[v].vis = true;
    for (int u : graph[v].prev) if (!graph[u].vis) dfs2(u, comp);
    graph[v].id = comp;
    sccs[comp].num++;
    sccs[comp].a += graph[v].a;
}

void dfsscc(int v) {
    sccs[v].vis = true;
    for (int u : sccs[v].next) {
        if (!sccs[u].vis) dfsscc(u);
        if (sccs[u].path + sccs[v].num > sccs[v].path) {
            sccs[v].path = sccs[u].path + sccs[v].num;
            sccs[v].total = sccs[v].a + sccs[u].total;
        } else if (sccs[u].path + sccs[v].num == sccs[v].path) {
            sccs[v].total = min(sccs[v].total, sccs[v].a + sccs[u].total);
        }
    }

    if (sccs[v].num > sccs[v].path) {
        sccs[v].path = sccs[v].num;
        sccs[v].total = sccs[v].a;
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;
        graph.clear();
        ord.clear();
        sccs.clear();
        for (int i = 0; i < N; i++) {
            node cur;
            cin >> cur.a;
            graph.push_back(cur);
        }
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].prev.push_back(u);
        }
        for (int i = 0; i < N; i++) if (!graph[i].vis) dfs1(i);
        for (int i = 0; i < N; i++) graph[i].vis = false;
        reverse(ord.begin(), ord.end());

        int comps = -1;
        for (int v : ord) {
            if (!graph[v].vis) {
                comps++;
                sccs.push_back({});
                dfs2(v, comps);
            }
        }

        for (int v = 0; v < N; v++) {
            for (int u : graph[v].next) {
                if (graph[u].id == graph[v].id) continue;
                sccs[graph[v].id].next.push_back(graph[u].id);
            }
        }

        for (int i = 0; i <= comps; i++) {
            if (!sccs[i].vis) dfsscc(i);
        }
        int maxlen = -1;
        ll minscore = 1e18;
        for (int i = 0; i <= comps; i++) {
            if (sccs[i].path > maxlen) {
                maxlen = sccs[i].path;
                minscore = sccs[i].total;
            } else if (sccs[i].path == maxlen) {
                minscore = min(minscore, sccs[i].total);
            }
        }

        cout << maxlen << " " << minscore << endl;
    }
}