// https://atcoder.jp/contests/abc259/tasks/abc259_f

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
    vector<plli> next;
    int d;
    ll pw = -1;

    // dp1 is the max weight choosable in the subtree of v using at most d incident edges
    // dp2 is the max weight choosable in the subtree of v using at most d-1 incident edges
    // dp2 <= dp1
    ll dp1, dp2;
};
node graph[300000];

void dfs(int cur, int parent) {
    vector<ll> diffs;

    ll total = 0;
    for (auto [w, next] : graph[cur].next) {
        if (next == parent) continue;

        graph[next].pw = w;
        dfs(next, cur);
        total += graph[next].dp1;
        diffs.push_back(graph[next].dp2 + w - graph[next].dp1);
    }

    graph[cur].dp1 = total;
    graph[cur].dp2 = total;
    
    int end = diffs.size();
    end = min(end, graph[cur].d);
    sort(diffs.begin(), diffs.end(), greater<ll>());

    for (int i = 0; i < end; i++) {
        graph[cur].dp1 += max(0ll, diffs[i]);
    } 
    end = diffs.size();
    end = min(end, graph[cur].d - 1);
    for (int i = 0; i < end; i++) {
        graph[cur].dp2 += max(0ll, diffs[i]);
    }

    if (graph[cur].d == 0) graph[cur].dp2 = -1e15;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> graph[i].d;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        graph[u].next.push_back({w, v});
        graph[v].next.push_back({w, u});
    }
    dfs(0, -1);

    cout << graph[0].dp1;
}