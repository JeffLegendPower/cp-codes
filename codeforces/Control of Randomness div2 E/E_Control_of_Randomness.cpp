// https://codeforces.com/contest/2040/problem/E

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

ll MOD = 998244353;

ll binpow(ll a, ll b, ll MOD) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll modinv(ll x, ll MOD) {
    return binpow(x, MOD - 2, MOD);
}

struct node {
    vector<int> next;
    int p;

    vector<ll> E;
};
vector<node> graph;

void dfs(int v, int p, int N) {
    graph[v].p = p;

    ll numC = 0;
    for (int x : graph[v].next) {
        if (x == p) continue;
        numC++;
    }

    if (p == 0) {
        graph[v].E.push_back(2*numC + 1);
        for (int i = 1; i <= N; i++) {
            graph[v].E.push_back(1);
        }
    } else if (p > 0) {
        int p2 = graph[p].p;
        graph[v].E.push_back(2*numC + graph[p2].E[0] + 2);
        for (int i = 1; i <= N; i++) {
            graph[v].E.push_back(min(
                graph[p2].E[i-1] + 2,
                2*numC + graph[p2].E[i] + 2
            ));
        }
    }

    for (int x : graph[v].next) {
        if (x == p) continue;
        dfs(x, v, N);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        
        graph.clear();
        for (int i = 0; i < N; i++) graph.push_back({});
        for (int i = 0; i < N - 1; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        }

        for (int i = 0; i <= N; i++) graph[0].E.push_back(0);

        dfs(0, -1, N);

        while (Q--) {
            int v, p;
            cin >> v >> p;
            v--;
            if (v == 0) cout << 0 << endl;
            else {
                v = graph[v].p;
                cout << graph[v].E[p] + 1 << endl;
            }
        }
    }
}