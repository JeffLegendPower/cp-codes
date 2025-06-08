// https://usaco.org/index.php?page=viewproblem2&cpid=1306&lang=en

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
    
    ll a = 0;
    ll dp = 0;

    // time to visit all the vertices in this subtree and come back to the start
    ll time = 0;
    // sum of a in all vertices of this subtree
    ll suma = 0;
};
node graph[200000]

void dfs(int x) {
    graph[x].suma = graph[x].a;
    graph[x].dp = graph[x].a;

    for (int v : graph[x].next) {
        graph[x].time += graph[v].time;
        graph[x].suma += graph[v].suma;

        graph[x].dp += graph[v].dp;
    }

    // we need to order the children to minimize the total dp cost
    // cost for each child will be the time to first reach that child (so time of all children before it) * suma of child
    // + dp cost of child
    
    // dp cost isnt affected by order so we can ignore it
    // and we see that chosing some child v is going to
    // and we see that choosing child with time t will increase dp cost by (suma of all children after it) * t

    // so we can greedily choose which child to pick first by seeing which one minimizes (current suma - suma of child) * t
    // = (current suma) * t - (child suma) * t
    // and we can sort and solve because lets say we pick one child v, (current suma) will

    // a1 = 20, t1 = 1000,    a2 = 10, t2 = 1, a3 = 3, t2 = 4

    vector<ll> dpt(1000, 0);
    for (int v : graph[x].next) {

    }

    ll t = 0;
    while (!graph[x].next.empty()) {
        t++;

        ll cost = 
        for (int v : graph[x].next) {
            graph[x].dp += 
        }
    }

}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, T; cin >> N >> T;

    for (int i = 1; i < N; i++) {
        int p; ll a;
        cin >> p >> a;
        p--;

        graph[p].next.push_back(i);
        graph[i].a = a;
    }
}