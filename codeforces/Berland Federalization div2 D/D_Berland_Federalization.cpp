// https://codeforces.com/problemset/problem/440/D

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
int K;
struct node {
    vector<pii> next;
    int pidx;

    // min number of extra states to split into if picking state from
    // this subtree with i nodes including the root
    ll dp[401];
    vector<int> edgs[401];
};
node graph[400];

void dfs(int cur, int parent) {
    ll children = 0;
    for (auto [idx, next] : graph[cur].next) {
        if (next == parent) {
            graph[cur].pidx = idx;
            continue;
        }
        dfs(next, cur);

        graph[cur].edgs[1].push_back(idx);
        children++;
    }

    for (int i = 0; i <= K; i++) graph[cur].dp[i] = 1e9;
    graph[cur].dp[1] = children;

    for (auto [idx, next] : graph[cur].next) {
        if (next == parent) continue;

        vector<int> addd(K + 1, -1);
        for (int i = K; i >= 1; i--) {
            for (int j = 1; j < i; j++) {
                if (graph[cur].dp[i - j] + graph[next].dp[j] - 1 < graph[cur].dp[i]) {
                    graph[cur].dp[i] = graph[cur].dp[i - j] + graph[next].dp[j] - 1;
                    addd[i] = j;
                }
                graph[cur].dp[i] = min(graph[cur].dp[i], graph[cur].dp[i - j] + graph[next].dp[j] - 1);
            }
        }

        for (int i = K; i >= 1; i--) {
            if (addd[i] == -1) continue;
            int j = addd[i];

            graph[cur].edgs[i].clear();
            for (int edg : graph[cur].edgs[i - j]) {
                if (edg == graph[next].pidx) continue;
                graph[cur].edgs[i].push_back(edg);
            } for (int edg : graph[next].edgs[j]) graph[cur].edgs[i].push_back(edg);
        }
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N >> K;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back({i + 1, v});
        graph[v].next.push_back({i + 1, u});
    }

    dfs(0, -1);

    ll best = 1e12;
    vector<int> edgs;
    for (int i = 0; i < N; i++) {
        if (graph[i].dp[K] + (i > 0) < best) {
            best = graph[i].dp[K] + (i > 0);
            edgs.clear();
            for (int edg : graph[i].edgs[K]) edgs.push_back(edg);
            if (i > 0) edgs.push_back(graph[i].pidx);
        }
        best = min(best, graph[i].dp[K] + (i > 0));
    }
    cout << best << endl;
    for (int edg : edgs) cout << edg << " ";
}