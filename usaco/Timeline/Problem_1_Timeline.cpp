// https://usaco.org/index.php?page=viewproblem2&cpid=1017

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
    ll mintime;
    bool searched = false;
    // {time diff, idx}
    vector<plli> next;
};
node graph[100000];

vector<int> topo;
void toposort(int cur) {
    graph[cur].searched = true;

    for (auto [x, next] : graph[cur].next) {
        if (graph[next].searched) continue;
        toposort(next);
    }
    
    topo.push_back(cur);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("timeline");

    int N, M, C;
    cin >> N >> M >> C;

    for (int i = 0; i < N; i++) {
        ll S;
        cin >> S;
        graph[i].mintime = S;
    }

    for (int i = 0; i < C; i++) {
        int a, b;
        ll x;
        cin >> a >> b >> x;
        a--, b--;
        graph[a].next.push_back({x, b});
    }

    for (int i = 0; i < N; i++) if (!graph[i].searched) toposort(i);
    reverse(topo.begin(), topo.end());

    for (int i : topo) {
        for (auto [x, next] : graph[i].next) {
            graph[next].mintime = max(graph[next].mintime, graph[i].mintime + x);
        }
    }

    for (int i = 0; i < N; i++) {
        cout << graph[i].mintime;
        if (i < N - 1) cout << endl;
    }
}