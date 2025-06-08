// https://codeforces.com/contest/838/problem/B

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

// rng increment updates
// point increment updates
// rng min queries
// point sum queries

// t1: only for edges going down, weight to get from root to edge i
// t2: for down edges and edges going to 1, min weight across range to get from root to edge and back to root
const int Nmax = 3e5;  // limit for array size
int N;  // array size
int h;
ll t1[2 * Nmax], t2[2 * Nmax];
ll d1[Nmax], d2[Nmax];

void calc(int p, ll k) {

    t1[p] = t1[p<<1] + t1[p<<1|1] + d1[p] * k;
    t2[p] = min(t2[p<<1], t2[p<<1|1]) + d2[p];
}


void apply1(int p, ll value, ll k) {
    t1[p] += value * k;
    if (p < N) d1[p] += value;
} void apply2(int p, ll value, ll k) {
    t2[p] += value;
    if (p < N) d2[p] += value;
}

void build(int l, int r) {
  int k = 2;
  for (l += N, r += N-1; l > 1; k <<= 1) {
    l >>= 1, r >>= 1;
    for (int i = r; i >= l; --i) calc(i, k);
  }
}

void push(int l, int r) {
  int s = h, k = 1 << (h-1);
  for (l += N, r += N-1; s > 0; --s, k >>= 1)
    for (int i = l >> s; i <= r >> s; ++i) {
        if (d1[i] != 0) {
            apply1(i<<1, d1[i], k);
            apply1(i<<1|1, d1[i], k);
            d1[i] = 0;
        } if (d2[i] != 0) {
            apply2(i<<1, d2[i], k);
            apply2(i<<1|1, d2[i], k);
            d2[i] = 0;
        }
    }
}

void modify(int l, int r, int value, bool onlyup) {
  if (value == 0) return;
  push(l, l + 1);
  push(r - 1, r);

  int l0 = l, r0 = r, k = 1;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {

    if (l&1) {
        if (!onlyup) apply1(l, value, k);
        apply2(l, value, k);
        l++;
    }
    if (r&1) {
        r--;
        if (!onlyup) apply1(r, value, k);
        apply2(r, value, k);
    }
  }
  build(l0, l0 + 1);
  build(r0 - 1, r0);
}

ll query1(int l, int r) {
  push(l, l + 1);
  push(r - 1, r);
  ll res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t1[l++];
    if (r&1) res += t1[--r];
  }
  return res;
} ll query2(int l, int r) {
  push(l, l + 1);
  push(r - 1, r);
  ll res = 1e18;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t2[l++]);
    if (r&1) res = min(res, t2[--r]);
  }
  return res;
}
// Segtree end

struct edge {
    int u, v;
    ll w;
};
struct node {
    vector<int> next;
    int parent;
    ll wup;

    int start, end;
};
node graph[200000];

int timer = 0;
void euler_tour(int cur, int parent) {
    graph[cur].start = timer++;
    graph[cur].parent = parent;
    
    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur);
    }
    graph[cur].end = timer;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int Q;
    cin >> N >> Q;

    h = sizeof(int) * 8 - __builtin_clz(N);

    vector<edge> edgs;
    for (int i = 0; i < N - 1; i++) {
        edge cur;
        cin >> cur.u >> cur.v >> cur.w;
        cur.u--, cur.v--;
        graph[cur.u].next.push_back(cur.v);
        graph[cur.v].wup = cur.w;
        edgs.push_back(cur);
    }
    euler_tour(0, -1);
    for (int i = 0; i < N - 1; i++) {
        edge cur;
        cin >> cur.u >> cur.v >> cur.w;
        cur.u--, cur.v--;
        graph[cur.u].next.push_back(cur.v);
        edgs.push_back(cur);
    }

    for (int i = 0; i < N - 1; i++) {
        int u = edgs[i].v;
        modify(graph[u].start, graph[u].end, edgs[i].w, false);
    } for (int i = N - 1; i < 2*N - 2; i++) {
        int u = edgs[i].u;
        modify(graph[u].start, graph[u].start + 1, edgs[i].w, true);
    }

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int i;
            ll w;
            cin >> i >> w;
            i--;
            
            if (i < N - 1) {
                int u = edgs[i].v;
                modify(graph[u].start, graph[u].end, w - edgs[i].w, false);
            } else {
                int u = edgs[i].u;
                modify(graph[u].start, graph[u].start + 1, w - edgs[i].w, true);
            }
            edgs[i].w = w;
        } else if (t == 2) {
            int u, v;
            cin >> u >> v;
            u--, v--;

            ll udist = query1(graph[u].start, graph[u].start + 1), vdist = query1(graph[v].start, graph[v].start + 1);

            // v is in the subtree of u or v = u
            if (graph[u].start <= graph[v].start && graph[u].end >= graph[v].end) {
                cout << vdist - udist << endl;
            } else { // v is not in the subtree of u
                ll utop = query2(graph[u].start, graph[u].end);
                cout << utop - udist + vdist << endl;
            }
        }
    }
}