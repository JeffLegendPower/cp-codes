// https://cses.fi/problemset/task/1139

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
const int Nmax = 2e5;  // limit for array size
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

struct qry {
    int idx;
    int a, b;
    int ans;
};

struct node {
    vector<int> next;
    ll color;

    int start = -1, end = -1;
};
node graph[200000];

int timer = 0;
int sorted[200000];
void euler_tour(int cur, int parent) {
    sorted[timer] = cur;
    graph[cur].start = timer++;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur);
    }
    graph[cur].end = timer;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> graph[i].color;
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }
    euler_tour(0, -1);

    map<ll, vector<int>> colors;
    for (int idx = N - 1; idx >= 0; idx--) {
        int i = sorted[idx];
        ll c = graph[i].color;

        if (colors[c].size() > 0) {
            t[N + colors[c].back()] = 0;
        } colors[c].push_back(idx);
        t[N + idx] = 1;
    }
    build();

    vector<qry> qs;
    for (int i = 0; i < N; i++) {
        qs.push_back({i, graph[i].start, graph[i].end, -1});
    }
    sort(qs.begin(), qs.end(), [](qry one, qry two) {
        return one.a < two.a;
    });

    int left = 0;
    for (int i = 0; i < N; i++) {

        while (left < qs[i].a) {
            ll c = graph[sorted[left]].color;
            modify(left, 0);
            colors[c].pop_back();

            if (colors[c].size() > 0) {
                modify(colors[c].back(), 1);
            }

            left++;
        }

        qs[i].ans = query(qs[i].a, qs[i].b);
    }

    sort(qs.begin(), qs.end(), [](qry one, qry two) {
        return one.idx < two.idx;
    });

    for (int i = 0; i < N; i++) cout << qs[i].ans << " ";
}