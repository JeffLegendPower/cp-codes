// https://codeforces.com/contest/1770/problem/D

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
    bool searched = false;
};
vector<node> graph;
int edges = 0;
int vertices = 0;

int selfloops = 0, cycles = 0;

void dfs(int curIdx, int parent) {
    graph[curIdx].searched = true;
    vertices++;
    
    for (int next : graph[curIdx].next) {
        edges++;

        if (next == curIdx) selfloops++;
        else if (graph[next].searched) cycles++;

        if (!graph[next].searched) dfs(next, curIdx);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    int T2 = T;

    while (T--) {
        int N;
        cin >> N;
        graph.clear();

        for (int i = 0; i < N; i++) {
            graph.push_back({});
        }

        int a[N], b[N];
        for (int i = 0; i < N; i++) cin >> a[i];
        for (int i = 0; i < N; i++) {
            cin >> b[i];
            graph[a[i] - 1].next.push_back(b[i] - 1);
            graph[b[i] - 1].next.push_back(a[i] - 1);
        }

        selfloops = 0, cycles = 0;
        bool possible = true;

        for (int i = 0; i < N; i++) {
            if (graph[i].searched) continue;

            edges = 0, vertices = 0;

            dfs(i, -1);
            edges /= 2;
            if (edges != vertices) {
                possible = false;
                break;
            }
        }

        selfloops /= 2;
        cycles -= N - selfloops;

        if (!possible) {
            cout << 0 << endl;
            continue;
        }

        ll res = 1;
        ll MOD = 998244353;

        while (selfloops--) {
            res = (res * N) % MOD;
        } while (cycles--) {
            res = (res * 2) % MOD;
        }

        cout << res << endl;
    }
}