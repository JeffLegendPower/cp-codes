// https://oj.uz/problem/view/IOI11_race

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

const int MAXN = 4e5;

struct node {
    vector<plli> next;
    ll dist = 0;
    int dep = 0;
};
node graph[MAXN];

map<ll, ll> dists[MAXN];
ll mindist = 1e18;
void dfs(int v, int p, ll K) {
    for (auto [w, x] : graph[v].next) {
        if (x == p) continue;
        graph[x].dist = graph[v].dist + w;
        graph[x].dep = graph[v].dep + 1;
        dfs(x, v, K);
    }

    // dists[v].insert({graph[v].dist, graph[v].dep});
    dists[v][graph[v].dist] = graph[v].dep;

    for (auto [w, x] : graph[v].next) {
        if (x == p) continue;

        if (dists[x].size() > dists[v].size()) swap(dists[x], dists[v]);
        // for (auto [dist, dep] : dists[x]) {
        for (auto itr = dists[x].begin(); itr != dists[x].end(); itr++) {
            ll dist = itr->first;
            ll dep = itr->second;

            ll target = K + 2*graph[v].dist - dist;

            // dist + target = K + 2*graph[v].dist
            // auto itr2 = dists[v].lower_bound({target, 0});

            if (dists[v].find(target) != dists[v].end()) {
            // if (itr2 != dists[v].end() && itr2->first == target) {
                mindist = min(mindist, dep + dists[v][target] - 2*graph[v].dep);
            }

            if (dists[v].find(dist) == dists[v].end()) dists[v][dist] = dep;
            else dists[v][dist] = min(dists[v][dist], dep);
        }
    }
}


int best_path(int N, int K, int H[][2], int L[]) {
    mindist = 1e18;
    for (int i = 0; i < N-1; i++) {
        auto [u, v] = H[i];
        ll w = L[i];

        graph[u].next.push_back({w, v});
        graph[v].next.push_back({w, u});
    }

    dfs(0, -1, K);

    // cout << mindist << endl;


    return (mindist == 1e18 ? -1 : mindist);
}

// int main() {
//     // Comment out for interactive problems
//     ios::sync_with_stdio(false);
// 	cin.tie(nullptr);

//     int N;
//     int K;
//     cin >> N >> K;

//     int H[N-1][2];
//     int L[N-1];
//     for (int i = 0; i < N-1; i++) {
//         cin >> H[i][0] >> H[i][1];
//     } for (int i = 0; i < N-1; i++) cin >> L[i];

//     cout << best_path(N, K, H, L);
// }