// https://atcoder.jp/contests/abc202/tasks/abc202_e

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

struct qry {
    int U, D;
    int idx;
    int ans;
};
struct node {
    vector<int> next;

    int start, end;
    int height;
};
node graph[200000];

int timer = 0;
void euler_tour(int cur, int parent, int height) {
    graph[cur].start = timer++;
    graph[cur].height = height;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur, height + 1);
    }
    
    graph[cur].end = timer;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        p--;
        graph[p].next.push_back(i);
    }
    euler_tour(0, -1, 0);

    vector<int> numheight[N];
    for (int i = 0; i < N; i++) numheight[graph[i].height].push_back(i);

    int Q;
    cin >> Q;
    qry qs[Q];
    for (int i = 0; i < Q; i++) {
        cin >> qs[i].U >> qs[i].D;
        qs[i].idx = i;
    } sort(qs, qs + Q, [](qry one, qry two) {
        return one.D < two.D;
    });

    for (int v : numheight[0]) modify(graph[v].start, 1);

    int height = 0;
    for (int q = 0; q < Q; q++) {
        while (height < qs[q].D) {
            for (int v : numheight[height]) modify(graph[v].start, 0);
            height++;
            for (int v : numheight[height]) modify(graph[v].start, 1);
        }

        qs[q].ans = query(graph[qs[q].U - 1].start, graph[qs[q].U - 1].end);
    }
    sort(qs, qs + Q, [](qry one, qry two) {
        return one.idx < two.idx;
    });

    for (qry q : qs) cout << q.ans << endl;
}