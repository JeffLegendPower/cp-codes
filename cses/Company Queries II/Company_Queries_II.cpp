// https://cses.fi/problemset/task/1688

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
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 4e5;  // limit for array size
int N;  // array size
// {employee, height}
pii t[2 * Nmax];

pii oper(pii a, pii b) {
    if (a.second < b.second) return a;
    else return b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

int query(int l, int r) {  // on interval [l, r)
  pii res = {-1, 1e6};
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res.first;
}
// Segtree end


struct node {
    vector<int> next;
    int height;

    int tourfirst;
};
node graph[200000];

int timer = 0;
int euler[400000];

void euler_tour(int cur, int parent, int height) {
    graph[cur].height = height;

    graph[cur].tourfirst = timer;
    euler[timer++] = cur;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur, height + 1);

        euler[timer++] = cur;
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, Q;
    cin >> n >> Q;

    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        graph[p - 1].next.push_back(i);
    }

    euler_tour(0, -1, 0);

    N = timer;
    for (int i = 0; i < timer; i++) t[N + i] = {euler[i], graph[euler[i]].height};
    build();

    while (Q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        int x = graph[a].tourfirst, y = graph[b].tourfirst;

        cout << (query(min(x, y), max(x, y) + 1) + 1) << endl;
    }
}