// https://codeforces.com/contest/1671/problem/E

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

ll MOD = 998244353;

struct node {
    ll dp;
    char c;
    string s;
};
vector<node> graph;

void dfs(int N, int idx) {
    if (idx * 2 > N) {
        graph[idx - 1].dp = 1;
        graph[idx - 1].s = graph[idx - 1].c;
        return;
    }

    dfs(N, idx * 2);
    dfs(N, idx * 2 + 1);

    graph[idx - 1].dp = (graph[(idx * 2) - 1].dp * graph[(idx * 2 + 1) - 1].dp) % MOD;

    if (graph[(idx * 2) - 1].s != graph[(idx * 2 + 1) - 1].s) graph[idx - 1].dp = (graph[idx - 1].dp * 2) % MOD;

    graph[idx - 1].s = graph[idx - 1].c;
    if (graph[(idx * 2) - 1].s <= graph[(idx * 2 + 1) - 1].s) {
        graph[idx - 1].s += graph[(idx * 2) - 1].s + graph[(idx * 2 + 1) - 1].s;
    } else graph[idx - 1].s += graph[(idx * 2 + 1) - 1].s + graph[(idx * 2) - 1].s;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    string s;
    cin >> s;

    for (int i = 0; i < (1<<N) - 1; i++) {
        node cur;
        cur.c = s[i];
        graph.push_back(cur);
    }

    dfs((1<<N) - 1, 1);

    cout << graph[0].dp;
}