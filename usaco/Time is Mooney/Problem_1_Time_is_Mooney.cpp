// https://usaco.org/index.php?page=viewproblem2&cpid=993

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

    // max score if ending at this node at time t
    // dp[t]
    ll dp[1001];
    vector<int> next;

    ll m;
};
node graph[1000];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("time");

    int N, M, C;
    cin >> N >> M >> C;

    for (int i = 0; i < N; i++) {
        cin >> graph[i].m;

        for (int t = 0; t < 1001; t++) graph[i].dp[t] = -1;
    }
    graph[0].dp[0] = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].next.push_back(v - 1);
    }

    for (int t = 0; t < 1000; t++) {
        for (int i = 0; i < N; i++) {
            if (graph[i].dp[t] == -1) continue;

            for (int next : graph[i].next) {
                graph[next].dp[t + 1] = max(graph[next].dp[t + 1], graph[i].dp[t] + graph[next].m);
            }
        }
    }

    ll best = 0;
    for (int t = 0; t < 1001; t++) {
        best = max(best, graph[0].dp[t] - C * t * t);
    }

    cout << best << endl;
}