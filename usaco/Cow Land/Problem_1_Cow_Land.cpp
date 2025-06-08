// https://usaco.org/index.php?page=viewproblem2&cpid=921

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define int long long
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
ll t[2 * Nmax];

void modify(int l, int r, ll value) {
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] ^= value;
    if (r&1) t[--r] ^= value;
  }
}

ll query(int p) {
  ll res = 0;
  for (p += N; p > 0; p >>= 1) res ^= t[p];
  return res;
}


const int N2max = 4e5;
int N2;
pii t2[2 * N2max];

pii oper2(pii a, pii b) {
    if (a.second < b.second) return a;
    else return b;
}

void build2() {  // build the tree
  for (int i = N2 - 1; i > 0; --i) t2[i] = oper2(t2[i<<1], t2[i<<1|1]);
}

int query2(int l, int r) {  // on interval [l, r)
  pii res = {-1, 1e6};
  for (l += N2, r += N2; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper2(res, t2[l++]);
    if (r&1) res = oper2(res, t2[--r]);
  }
  return res.first;
}
// Segtree end


struct node {
    vector<int> next;
    ll e;

    int start = -1, end = -1;
    int time;
    int height;
};
node graph[100000];

int euler[200000];
int timer = 0, timer2 = 0;
void euler_tour(int cur, int parent, int height) {
    graph[cur].height = height;
    graph[cur].start = timer++;

    graph[cur].time = timer2;
    euler[timer2++] = cur;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur, height + 1);
        euler[timer2++] = cur;
    }

    graph[cur].end = timer;
}

signed main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("cowland");

    int Q;
    cin >> N >> Q;

    for (int i = 0; i < N; i++) cin >> graph[i].e;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }
    euler_tour(0, -1, 0);

    for (int i = 0; i < N; i++) {
        modify(graph[i].start, graph[i].end, graph[i].e);
    }

    N2 = timer2;
    for (int i = 0; i < timer2; i++) {
        t2[N2 + i] = {euler[i], graph[euler[i]].height};
    }
    build2();

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int i;
            ll v;
            cin >> i >> v;
            i--;

            modify(graph[i].start, graph[i].end, graph[i].e);
            modify(graph[i].start, graph[i].end, v);

            graph[i].e = v;
        } else if (t == 2) {
            int i, j;
            cin >> i >> j;
            i--, j--;

            int itime = graph[i].time, jtime = graph[j].time;
            int p = query2(min(itime, jtime), max(itime, jtime) + 1);

            cout << (query(graph[i].start) ^ query(graph[j].start) ^ graph[p].e) << endl;
        }
    }
}