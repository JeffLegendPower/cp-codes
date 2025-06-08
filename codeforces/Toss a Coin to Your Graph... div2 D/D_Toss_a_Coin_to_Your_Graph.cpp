// https://codeforces.com/contest/1679/problem/D

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
    vector<int> next;
    ll val;
    bool searched = false;
    int chainsize = 1;
};
vector<node> graph;
vector<bool> cyclicstack;

bool cyclic(int curIdx, ll bound) {
    cyclicstack[curIdx] = true;
    graph[curIdx].searched = true;

    bool iscyclic = false;
    for (int next : graph[curIdx].next) {
        if (graph[next].val > bound) continue;
        if (cyclicstack[next]) {
            cyclicstack[curIdx] = false;
            return true;
        } if (graph[next].searched) continue;

        iscyclic |= cyclic(next, bound);
    }

    cyclicstack[curIdx] = false;
    return iscyclic;
}
ll dfs(int curIdx, ll bound) {
    graph[curIdx].searched = true;

    int nextchain = 0;
    for (int next : graph[curIdx].next) {
        if (graph[next].val > bound) continue;
        if (!graph[next].searched) dfs(next, bound);
        nextchain = max(nextchain, graph[next].chainsize);
    }

    graph[curIdx].chainsize = 1 + nextchain;
    return graph[curIdx].chainsize;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    ll k;
    cin >> N >> M >> k;

    for (int i = 0; i < N; i++) {
        node cur;
        cin >> cur.val;
        graph.push_back(cur);
        cyclicstack.push_back(false);
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;

        graph[u - 1].next.push_back(v - 1);
    }
    
    ll low = 0, high = 1e9;
    ll best = -1;
    while (low <= high) {
        ll mid = low + (high - low) / 2;

        for (int i = 0; i < N; i++) {
            graph[i].searched = false;
            graph[i].chainsize = 0;
        }

        bool iscyclic = false;
        for (int i = 0; i < N; i++) {
            if (graph[i].val <= mid) iscyclic |= cyclic(i, mid);
        }

        if (iscyclic) {
            high = mid - 1;
            best = mid;
            continue;
        }

        for (int i = 0; i < N; i++) {
            graph[i].searched = false;
            graph[i].chainsize = 0;
        }

        ll maxchain = 0;
        for (int i = 0; i < N; i++) {
            if (graph[i].val <= mid) maxchain = max(maxchain, dfs(i, mid));
        }
        if (maxchain >= k) {
            high = mid - 1;
            best = mid;
        } else low = mid + 1;
    }

    cout << best << endl;
}