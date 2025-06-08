// https://usaco.org/index.php?page=viewproblem2&cpid=814

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
    vector<int> next;

    ll l;
    ll files;
    bool file;

    // total length for subtree, total length outside of subtree
    ll dpf, dpg;
};
node graph[100000];
ll files = 0;

void dfs(int cur, int parent) {
    for (int next : graph[cur].next) {
        if (next == parent) continue;
        if (graph[next].file) {
            graph[cur].dpf += graph[next].l;
            graph[cur].files++;
            continue;
        }
        dfs(next, cur);
        graph[cur].dpf += graph[next].dpf + graph[next].files * (graph[next].l + 1);
        graph[cur].files += graph[next].files;
    }
} void dfs2(int cur, int parent) {
    ll lengths = graph[cur].dpf;
    for (int next : graph[cur].next) {
        if (next == parent || graph[next].file) continue;
        lengths -= graph[next].dpf + graph[next].files * (graph[next].l + 1);

        graph[next].dpg = lengths + 3 * (files - graph[next].files) + graph[cur].dpg;

        lengths += graph[next].dpf + graph[next].files * (graph[next].l + 1);

        dfs2(next, cur);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("dirtraverse");

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        string s;
        int m;
        cin >> s >> m;
        graph[i].l = s.size();
        if (m == 0) {
            graph[i].file = true;
            files++;
            graph[i].dpf = 1e12;
        } else {
            while (m--) {
                int next;
                cin >> next;
                graph[i].next.push_back(next - 1);
            }
        }
    }
    dfs(0, -1);
    dfs2(0, -1);

    ll best = 1e18;
    for (int i = 0; i < N; i++) best = min(best, graph[i].dpf + graph[i].dpg);
    cout << best;
}