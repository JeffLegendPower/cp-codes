// https://atcoder.jp/contests/abc373/tasks/abc373_d

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
    bool searched = false;
    vector<plli> next;
    vector<int> par;

    ll val;
    bool set = false;
};
vector<node> graph;

vector<int> touched;

// must be started by a full parent (going all the way up tree)
void dfs(int curIdx, int parent, ll w) {
    graph[curIdx].searched = true;

    if (graph[curIdx].set) {
        ll expect = graph[parent].val + w;
        ll diff = graph[curIdx].val - expect;

        // cout << "E " << diff << endl;

        while (touched.size() > 0) {
            graph[touched.back()].val += diff;
            touched.pop_back();
        }

        return;
    }

    graph[curIdx].set = true;
    if (parent == -1) graph[curIdx].val = 0;
    else graph[curIdx].val = graph[parent].val + w;

    touched.push_back(curIdx);

    for (plli next : graph[curIdx].next) {
        if (next.second == parent) continue;
        dfs(next.second, curIdx, next.first);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) graph.push_back({});

    for (int i = 0; i < M; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        graph[u - 1].next.push_back({w, v - 1});
        graph[v - 1].par.push_back(u - 1);
    }

    for (int i = 0; i < N; i++) {
        int cur = i;
        if (graph[cur].searched) continue;
        touched.clear();

        graph[cur].searched = true;

        while (graph[cur].par.size() > 0) {
            if (graph[graph[cur].par.back()].searched) graph[cur].par.pop_back();
            else {
                cur = graph[cur].par.back();
                graph[cur].searched = true;
            }
        }

        // cout << cur << endl;
        dfs(cur, -1, 0);
    }

    for (int i = 0; i < N; i++) cout << graph[i].val << " ";
}