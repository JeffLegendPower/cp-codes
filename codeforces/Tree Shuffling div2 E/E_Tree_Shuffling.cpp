// https://codeforces.com/contest/1363/problem/E

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
    bool searched = false;
    vector<int> next;

    int digit;
    int goal;
    ll cost = 0;

    bool good = true;
    int num1 = 0, num0 = 0;
    int goal1 = 0, goal0 = 0;

    int numbad = 0;
};
vector<node> graph;

ll cost = 0;
pii dfs(int curIdx, ll mincost) {
    graph[curIdx].searched = true;
    mincost = min(mincost, graph[curIdx].cost);

    ll extra1 = 0, extra0 = 0;
    if (graph[curIdx].digit != graph[curIdx].goal) {
        if (graph[curIdx].digit == 1) extra1++;
        else extra0++;
    }

    for (int next : graph[curIdx].next) {
        if (graph[next].searched) continue;
        pii res = dfs(next, mincost);
        extra1 += res.first;
        extra0 += res.second;
    }

    ll num = min(extra1, extra0);
    cost += mincost * 2 * min(extra1, extra0);
    extra1 -= num;
    extra0 -= num;

    return {extra1, extra0};
}


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        node cur;
        cin >> cur.cost >> cur.digit >> cur.goal;
        graph.push_back(cur);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;

        graph[u - 1].next.push_back(v - 1);
        graph[v - 1].next.push_back(u - 1);
    }

    pii res = dfs(0, 1e18);
    if (res.first > 0 || res.second > 0) cout << -1 << endl;
    else cout << cost << endl;
}