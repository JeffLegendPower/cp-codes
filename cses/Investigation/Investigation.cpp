// https://cses.fi/problemset/task/1202

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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

ll MOD = 1e9 + 7;

struct node {
    vector<plli> next;
    bool searched = false;

    ll dist = 1e18;
    ll paths = 0;

    ll shortest = 1e9, longest = 0;
};
node graph[100000];

void dijkstra(int v) {
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> todo;

    // dist, vertex, prev
    todo.push({0, v, -1});

    while (!todo.empty()) {
        auto [dist, u, prev] = todo.top();
        todo.pop();

        ll paths = 1, shortest = -1, longest = -1;
        if (prev != -1) {
            paths = graph[prev].paths;
            shortest = graph[prev].shortest;
            longest = graph[prev].longest;
        }

        if (dist > graph[u].dist) continue;
        if (dist < graph[u].dist) {
            graph[u].paths = 0;
            graph[u].shortest = 1e9;
            graph[u].longest = 0;
        }

        graph[u].paths = (graph[u].paths + paths) % MOD;
        graph[u].shortest = min(graph[u].shortest, shortest + 1);
        graph[u].longest = max(graph[u].longest, longest + 1);

        if (graph[u].dist != dist) for (auto [w, next] : graph[u].next) todo.push({dist + w, next, u});
        graph[u].dist = dist;
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M; cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;

        graph[u].next.push_back({w, v});
    }

    dijkstra(0);

    cout << graph[N - 1].dist << " " << graph[N - 1].paths << " " << graph[N - 1].shortest << " " << graph[N - 1].longest << endl;
}