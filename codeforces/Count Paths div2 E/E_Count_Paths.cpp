// https://codeforces.com/contest/1923/problem/E

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
    int color;
    vector<int> next;
    bool searched = false;

    vector<int> colornext;
};
node graph[(int) 1e6];

int parents[(int) 1e6];
int siblings[(int) 1e6];

ll total = 0;
void dfs(int curIdx) {
    graph[curIdx].searched = true;

    int color = graph[curIdx].color;
    total += siblings[color];
    total += parents[color] > 0;

    int before = siblings[color];
    siblings[color] = 0;
    parents[color]++;

    for (int next : graph[curIdx].next) {
        if (graph[next].searched) continue;

        dfs(next);
        siblings[color] = 0;
    }

    siblings[color] = before + 1;
    parents[color]--;
}


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        total = 0;

        for (int i = 0; i < N; i++) {
            node cur;
            cin >> cur.color;
            graph[i] = cur;
            parents[i + 1] = 0;
            siblings[i + 1] = 0;
        }

        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;

            graph[u - 1].next.push_back(v - 1);
            graph[v - 1].next.push_back(u - 1);
        }

        dfs(0);

        cout << total << endl;
    }
}