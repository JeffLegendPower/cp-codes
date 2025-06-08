// https://codeforces.com/problemset/problem/1800/G

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

struct node {
    vector<int> next;

    ll hsh = 99764571;
};
vector<node> graph;

ll MOD = 1e9 + 7;
map<ll, ll> hashes;

void dfs(int cur, int p) {
    ll in = 1;
    for (int next : graph[cur].next) {
        if (next == p) continue;
        dfs(next, cur);
        in = (in * graph[next].hsh) % MOD;
    }

    if (hashes.find(in) == hashes.end()) hashes[in] = uld(19427, 1e9 + 6);

    graph[cur].hsh = hashes[in];
}

bool works = true;
void dfs2(int cur, int p) {
    set<ll> cnts;

    bool children = 0;
    for (int next : graph[cur].next) {
        if (next == p) continue;

        ll hsh = graph[next].hsh;
        if (cnts.find(hsh) != cnts.end()) cnts.erase(hsh);
        else cnts.insert(hsh);

        children ^= 1;
    }

    if (!children && cnts.size() > 0) works = false;
    else if (children && cnts.size() > 1) works = false;
    else if (children && cnts.size() == 1) {
        ll hsh = *cnts.begin();

        for (int next : graph[cur].next) {
            if (next == p) continue;
            if (graph[next].hsh == hsh) {
                dfs2(next, cur);
                break;
            }
        }
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;

    while (T--) {
        int N; cin >> N;

        graph.clear();
        works = true;
        for (int i = 0; i < N; i++) graph.push_back({});
        for (int i = 0; i < N - 1; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        }

        dfs(0, -1);
        dfs2(0, -1);

        cout << (works ? "YES" : "NO") << endl;
    }
}