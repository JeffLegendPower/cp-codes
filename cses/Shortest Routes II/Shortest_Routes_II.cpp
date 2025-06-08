// https://cses.fi/problemset/task/1672

// If we tried to solve this using dijkstra's, we would TLE
// This is because dijkstra's can only calculate the distance from one vertex
// to every other vertex in O((V + E) * logV). Since we need to run it V times,
// it would take O(V * (V + E) * logV) time. This is too slow. However, Floyd-Warshall
// can calculate the distance between every pair of vertices in one pass. However, it takes
// O(V^3) time. This is okay since n <= 500 and O(500^3) will not TLE

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
    vector<plli> next;
};

vector<node> graph;
vector<vector<ll>> dists;

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;

    for (int i = 0; i < N; i++) {
        graph.push_back({});
        dists.push_back({});
        for (int j = 0; j < N; j++) {
            dists[i].push_back(1e18);
        }
    }

    // Floyd-Warshall
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) dists[i][j] = 0;
            else dists[i][j] = 1e18;
        }
    }

    for (int i = 0; i < M; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        graph[a - 1].next.push_back({c, b - 1});
        graph[b - 1].next.push_back({c, a - 1});


        dists[a - 1][b - 1] = min(dists[a - 1][b - 1], c);
        dists[b - 1][a - 1] = min(dists[b - 1][a - 1], c);
    }

    // Floyd-Warshall
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
            }
        }
    }

    while (Q--) {
        int a, b;
        cin >> a >> b;
        ll ans = dists[a - 1][b - 1];
        if (ans == 1e18) cout << -1;
        else cout << ans;
        cout << endl;
    }
}