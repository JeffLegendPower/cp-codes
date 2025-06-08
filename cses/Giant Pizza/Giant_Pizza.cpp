// https://cses.fi/problemset/task/1684

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
    vector<int> prev;

    bool searched = false;

    int scc = -1;
};
node graph[200000];

vector<int> topo;
void toposort(int x) {
    graph[x].searched = true;
    for (int v : graph[x].next) if (!graph[v].searched) toposort(v);
    topo.push_back(x);
}

vector<node> cond;
int k = 0;
void dfs(int x, int scc) {
    graph[x].searched = true;
    graph[x].scc = scc;

    for (int v : graph[x].prev) if (!graph[v].searched) dfs(v, scc);
}

int cnt = 0;
void toposort2(int x) {
    cond[x].searched = true;
    for (int v : cond[x].next) if (!cond[v].searched) toposort2(v);
    cond[x].scc = cnt--;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M; cin >> N >> M;

    for (int i = 0; i < N; i++) {
        int a, b;
        char c1, c2;
        cin >> c1 >> a >> c2 >> b;
        a--, b--;

        int b1 = c1 == '+', b2 = c2 == '+';

        graph[2*a + (b1^1)].next.push_back(2*b + b2);
        graph[2*b + b2].prev.push_back(2*a + (b1^1));

        graph[2*b + (b2^1)].next.push_back(2*a + b1);
        graph[2*a + b1].prev.push_back(2*b + (b2^1));
    }

    for (int i = 0; i < 2*M; i++) if (!graph[i].searched) toposort(i);
    reverse(topo.begin(), topo.end());
    for (int i = 0; i < 2*M; i++) graph[i].searched = false;

    int scc = -1;
    for (int i : topo) if (!graph[i].searched) {
        scc++;
        dfs(i, scc);
        cond.push_back({});
    }

    for (int i = 0; i < 2*M; i++) {
        int cur = graph[i].scc;
        for (int next : graph[i].next) if (graph[next].scc != cur) {
            cond[cur].next.push_back(graph[next].scc);
        }
    }

    for (int i = 0; i <= scc; i++) if (!cond[i].searched) toposort2(i);

    vector<bool> use(M);
    bool works = true;
    for (int i = 0; i < M; i++) {
        int scc1 = cond[graph[2*i + 1].scc].scc;
        int scc2 = cond[graph[2*i].scc].scc;

        if (scc1 > scc2) {
            use[i] = true;
        } else if (scc2 > scc1) {
            use[i] = false;
        } else works = false;
    }

    if (!works) cout << "IMPOSSIBLE";
    else {
        for (int i = 0; i < M; i++) cout << (use[i] ? "+ " : "- ");
    }
}