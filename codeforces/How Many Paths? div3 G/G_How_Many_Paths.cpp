// https://codeforces.com/contest/1547/problem/G

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
    int num = 0;
    bool searched = false;
    bool cycle = false;
};
node graph[400000];
bool stackk[400000];

void dfs(int cur, int set) {
    graph[cur].searched = true;
    graph[cur].num = set;
    stackk[cur] = true;

    for (int next : graph[cur].next) {
        if (graph[next].searched) {
            graph[next].num = max(graph[next].num, 2);
            if (stackk[next]) graph[next].num = 3;
        } else dfs(next, set);
    }

    stackk[cur] = false;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        for (int i = 0; i < N; i++) {
            graph[i].next.clear();
            graph[i].num = 0;
            graph[i].searched = false;
            graph[i].cycle = false;
        }

        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
        }
        dfs(0, 1);

        vector<int> path2;
        for (int i = 0; i < N; i++) {
            graph[i].searched = false;
            if (graph[i].num == 2) path2.push_back(i);
        } for (int i : path2) if (!graph[i].searched) dfs(i, 2);

        vector<int> pathinf;
        for (int i = 0; i < N; i++) {
            graph[i].searched = false;
            if (graph[i].num == 3) pathinf.push_back(i);
        } for (int i : pathinf) if (!graph[i].searched) dfs(i, 3);

        for (int i = 0; i < N; i++) {
            if (graph[i].num == 3) cout << -1 << " ";
            else cout << graph[i].num << " ";
        }
        cout << endl;
    }
}