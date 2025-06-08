// https://usaco.org/index.php?page=viewproblem2&cpid=790

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
    int id = -1;
    vector<int> next;
};
node graph[100001];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("atlarge");

    int N, K;
    cin >> N >> K;
    K--;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }

    // when bessie: id = 0, else id = farmer id
    // {vertex, id}
    deque<pii> todo;

    for (int i = 0; i < N; i++) {
        if (graph[i].next.size() == 1) {
            todo.push_back({i, i + 1});
            graph[i].id = i + 1;
        }
    }
    if (graph[K].id != -1) {
        cout << 1;
        return 0;
    }

    todo.push_back({K, 0});
    graph[K].id = 0;

    set<int> farmers;
    while (!todo.empty()) {
        auto [v, id] = todo.front();
        todo.pop_front();

        for (int next : graph[v].next) {
            if (graph[next].id == 0) continue;
            if (graph[next].id != -1) {
                if (id == 0) farmers.insert(graph[next].id);
                continue;
            }

            graph[next].id = id;
            todo.push_back({next, id});
        }
    }

    cout << farmers.size() << endl;
}