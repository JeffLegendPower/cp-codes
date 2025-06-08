// https://usaco.org/index.php?page=viewproblem2&cpid=970

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

void modify(int l, int r, int value) {
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}

int query(int p) {
  int res = 0;
  for (p += N; p > 0; p >>= 1) res += t[p];
  return res;
}

const int N2max = 2e5;  // limit for array size
int N2;  // array size
pii t2[2 * N2max];

pii oper(pii a, pii b) {
    if (a.second < b.second) return a;
    else return b;
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

struct qry {
    int a, b;
    int c;

    int idx;
    bool ans;
};

struct node {
    vector<int> next;
    int T;

    int start, end;
    int time;
    int height;  
};
node graph[100000];

int timer = 0, timer2 = 0;
int euler[200000];
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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("milkvisits");

    int M;
    cin >> N >> M;

    vector<int> vs[N + 1];

    for (int i = 0; i < N; i++) {
        cin >> graph[i].T;
        vs[graph[i].T].push_back(i);
    } for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }

    euler_tour(0, -1, 0);

    qry qs[M];
    for (int i = 0; i < M; i++) {
        cin >> qs[i].a >> qs[i].b >> qs[i].c;
        qs[i].a--, qs[i].b--;
        qs[i].idx = i;
    }
    sort(qs, qs + M, [](qry one, qry two) {
        return one.c < two.c;
    });

    N2 = timer2;
    for (int i = 0; i < timer2; i++) {
        t2[N2 + i] = {euler[i], graph[euler[i]].height};
    } build2();

    for (int v : vs[1]) {
        modify(graph[v].start, graph[v].end, 1);
    }

    int c = 1;
    for (int i = 0; i < M; i++) {
        while (c < qs[i].c) {
            for (int v : vs[c]) modify(graph[v].start, graph[v].end, -1);
            c++;
            for (int v : vs[c]) modify(graph[v].start, graph[v].end, 1);
        }

        int atime = graph[qs[i].a].time, btime = graph[qs[i].b].time;
        int p = query2(min(atime, btime), max(atime, btime) + 1);

        int num = query(graph[qs[i].a].start) + query(graph[qs[i].b].start) - 2 * query(graph[p].start);
        if (graph[p].T == c) num++;
        qs[i].ans = num > 0;
    }
    
    sort(qs, qs + M, [](qry one, qry two) {
        return one.idx < two.idx;
    });

    for (int i = 0; i < M; i++) cout << qs[i].ans;
}