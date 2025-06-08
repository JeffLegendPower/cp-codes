// https://codeforces.com/contest/1997/problem/D

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
    vector<int> children;
    int parent;
    bool searched = false;

    ll dpval;
};
vector<node> graph;

ll dfs(int curIdx) {
    ll minchildval = 1e18;
    for (int next : graph[curIdx].children) {
        minchildval = min(minchildval, dfs(next));
    }

    if (minchildval == 1e18) {
        // cout << curIdx << " e " << graph[curIdx].val << endl;
        return graph[curIdx].val;
    } if (curIdx == 0) {
        return graph[curIdx].val + minchildval;
    }

    ll curval = graph[curIdx].val;
    if (curval >= minchildval) return minchildval;

    curval += (minchildval - curval) / 2;

    // cout << curIdx << " k " << curval << endl;
    return curval;
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
            cin >> graph[i + 1].parent;
            graph[i + 1].parent--;
            graph[graph[i + 1].parent].children.push_back(i + 1);
        }

        cout << dfs(0) << endl;
    }
}