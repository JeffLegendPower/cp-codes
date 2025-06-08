// https://atcoder.jp/contests/abc294/tasks/abc294_g

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
const int Nmax = 2e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

void modify(int l, int r, ll value) {
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}

ll query(int p) {
  ll res = 0;
  for (p += N; p > 0; p >>= 1) res += t[p];
  return res;
}


const int N2max = 4e5;  // limit for array size
int N2;  // array size
pii t2[2 * N2max];

pii oper(pii a, pii b) {
    return (a.second < b.second ? a : b);
}

void build2() {  // build the tree
  for (int i = N2 - 1; i > 0; --i) t2[i] = oper(t2[i<<1], t2[i<<1|1]);
}

int query2(int l, int r) {  // on interval [l, r)
  pii res = {-1, 1e6};
  for (l += N2, r += N2; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t2[l++]);
    if (r&1) res = oper(res, t2[--r]);
  }
  return res.first;
}
// Segtree end

struct edge {
    int u, v;
    ll w;
};
struct node {
    vector<int> next;
    int parent;

    int start, end;
    int height;
    int time;
};
node graph[200000];

int euler[400000];
int timer = 0, timer2 = 0;
void euler_tour(int cur, int parent, int height) {
    graph[cur].start = timer++;
    graph[cur].parent = parent;
    // cout << cur << " " << graph[cur].start << endl;

    graph[cur].height = height;
    graph[cur].time = timer2;
    euler[timer2++] = cur;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur, height + 1);
        euler[timer2++] = cur;
    }

    graph[cur].end = timer;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N;

    edge edges[N - 1];

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;

        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
        // cout << u << " " << v << endl
        edges[i] = {u, v, w};
    }
    euler_tour(0, -1, 0);

    for (int i = 0; i < N - 1; i++) {
        if (graph[edges[i].u].parent != edges[i].v) swap(edges[i].u, edges[i].v);
        ll w = edges[i].w;
        int u = edges[i].u;

        modify(graph[u].start, graph[u].end, w);
    }

    N2 = timer2;
    for (int i = 0; i < N2; i++) {
        t2[N2 + i] = {euler[i], graph[euler[i]].height};
    }
    build2();

    int Q;
    cin >> Q;
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i;
            ll w;
            cin >> i >> w;
            i--;
            int u = edges[i].u;
            modify(graph[u].start, graph[u].end, w - edges[i].w);
            edges[i].w = w;
        } else if (t == 2) {
            int u, v;
            cin >> u >> v;
            u--, v--;

            int utime = graph[u].time, vtime = graph[v].time;
            int p = query2(min(utime, vtime), max(utime, vtime) + 1);

            cout << (query(graph[u].start) + query(graph[v].start) - 2 * query(graph[p].start)) << endl;
        }
    }
}