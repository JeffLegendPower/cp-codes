// https://open.kattis.com/problems/quantumsuperposition

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
    bool searched = false;
    vector<int> next;

    bool sums[1001];
};
vector<node> graph1, graph2;

void dfs1(int cur) {
    graph1[cur].searched = true;

    for (int next : graph1[cur].next) {
        if (!graph1[next].searched) dfs1(next);

        for (int i = 0; i < 1000; i++) graph1[cur].sums[i + 1] |= graph1[next].sums[i];
    }
}
void dfs2(int cur) {
    graph2[cur].searched = true;

    for (int next : graph2[cur].next) {
        if (!graph2[next].searched) dfs2(next);

        for (int i = 0; i < 1000; i++) graph2[cur].sums[i + 1] |= graph2[next].sums[i];
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N1, N2, M1, M2;
    cin >> N1 >> N2 >> M1 >> M2;

    for (int i = 0; i < N1; i++) graph1.push_back({});
    for (int i = 0; i < N2; i++) graph2.push_back({});

    graph1[N1 - 1].searched = true;
    graph1[N1 - 1].sums[0] = true;

    graph2[N2 - 1].searched = true;
    graph2[N2 - 1].sums[0] = true;

    for (int i = 0; i < M1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph1[u].next.push_back(v);
    }
    for (int i = 0; i < M2; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph2[u].next.push_back(v);
    }

    dfs1(0), dfs2(0);

    vector<bool> dp(2001, false);
    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            dp[i + j] = dp[i + j] | (graph1[0].sums[i] & graph2[0].sums[j]);
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int q;
        cin >> q;

        cout << (dp[q] ? "Yes" : "No") << endl;
    }
}