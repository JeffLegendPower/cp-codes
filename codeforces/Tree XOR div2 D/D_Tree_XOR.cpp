// https://codeforces.com/contest/1882/problem/D

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


struct comp {
    bool operator() (plli a, plli b) {
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
    ll val;
    bool searched;
    vector<int> next;

    int children = 0;

    // cost to fix each bit on the subtree rooted at 1
    // make sure to do 2^cost[i] at the end

    // cost to fix to 1
    ll cost1[30];
    // cost to fix to 0
    ll cost0[30];
};

vector<node> graph;


int dfs(int curIdx) {
    graph[curIdx].searched = true;
    for (int next : graph[curIdx].next) if (!graph[next].searched) graph[curIdx].children += dfs(next);

    for (int bit = 29; bit >= 0; bit--) {
        ll val = graph[curIdx].val;
        cost1[bit] = 0;
        cost0[bit] = 0;

        if (val & (1ll << bit)) {
            for (int next : graph[curIdx].next) 
        } else {

        }
    }

    return graph[curIdx].children + 1;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        graph.clear();

        for (int i = 0; i < N; i++) {
            node cur;
            cin >> cur.val;
            graph.push_back(cur);
        } for (int i = 0; i < N - 1; i++) {
            int a, b;
            cin >> a >> b;
            graph[a - 1].next.push_back(b - 1);
            graph[b - 1].next.push_back(a - 1);
        }
    }

    dfs(0);
}