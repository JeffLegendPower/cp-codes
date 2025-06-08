// https://codeforces.com/problemset/problem/852/D

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

vector<vector<pii>> graph;
vector<vector<int>> dists;

void dijkstra(int s) {
    priority_queue<pii, vector<pii>, greater<pii>> todo;

    dists[s][s] = 0;
    todo.push({0, s});
    while (!todo.empty()) {
        auto [d, v] = todo.top();
        todo.pop();

        for (auto [x, w] : graph[v]) {
            if (dists[s][x] <= d + w) continue;
            dists[s][x] = d + w;
            todo.push({d+w, x});
        }
    }
}

vector<vector<int>> graph2;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : graph2[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int V, E, N, K;
    cin >> V >> E >> N >> K;

    graph.resize(V);
    dists.assign(V, vector<int>(V, 1e9));

    vector<int> teams(N);
    for (int i = 0; i < N; i++) {
        cin >> teams[i];
        teams[i]--;
    }

    for (int i = 0; i < E; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--;

        graph[u].push_back({v, t});
        graph[v].push_back({u, t});
    }

    for (int i = 0; i < V; i++) dijkstra(i);


    int low = 0, high = 1731311;
    int best = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        mt.assign(V, -1);
        graph2.clear();
        graph2.resize(N);
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < V; j++) {
                if (dists[teams[i]][j] > mid) continue;
                graph2[i].push_back(j);
            }
        }

        for (int v = 0; v < N; v++) {
            used.assign(N, false);
            try_kuhn(v);
        }

        int cnt = 0;
        for (int i = 0; i < V; i++) cnt += mt[i] != -1;

        if (cnt >= K) {
            best = mid;
            high = mid - 1;
        } else low = mid + 1;
    }

    cout << best;
}