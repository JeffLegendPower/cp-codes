// https://codeforces.com/contest/1867/problem/D

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
    int next;
    bool searched = false;
    ll color = -1;
    ll group = -1;
    bool goodcycle = false;
    ll distfromgoodcycle = 1e18;
};

vector<node> graph;

void dfscycle(int curIdx) {
    graph[curIdx].goodcycle = true;
    graph[curIdx].distfromgoodcycle = 0;
    if (!graph[graph[curIdx].next].goodcycle) dfscycle(graph[curIdx].next);
}

void dfs(int curIdx, ll color, int K, ll group) {
    graph[curIdx].color = color;
    graph[curIdx].group = group;
    graph[curIdx].searched = true;
    if (!graph[graph[curIdx].next].searched) {
        dfs(graph[curIdx].next, color + 1, K, group);
    } else {
        if ((color - graph[graph[curIdx].next].color == K - 1) && graph[graph[curIdx].next].group == group) {
            // cout << curIdx << " " << graph[curIdx].next << endl;
            dfscycle(curIdx);
        }
    }
}

ll dfsdist(int curIdx) {
    if (graph[curIdx].goodcycle) return 0;
    graph[curIdx].searched = true;

    if (!graph[graph[curIdx].next].searched)
        graph[curIdx].distfromgoodcycle = min(graph[curIdx].distfromgoodcycle, dfsdist(graph[curIdx].next) + 1);
    else graph[curIdx].distfromgoodcycle = min(graph[curIdx].distfromgoodcycle, graph[graph[curIdx].next].distfromgoodcycle + 1);
    
    return graph[curIdx].distfromgoodcycle;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        graph.clear();

        bool works = true;
        int b[N];
        for (int i = 0; i < N; i++) {
            cin >> b[i];
            // if (b[i] == i + 1) works = false;
        }

        // if (K == 1) {
        //     cout << "YES" << endl;
        //     continue;
        // }

        for (int i = 0; i < N; i++) {
            node cur;
            cur.next = b[i] - 1;
            graph.push_back(cur);
        }

        for (int i = 0; i < N; i++) {
            if (!graph[i].searched) dfs(i, 0, K, i);
        } for (int i = 0; i < N; i++) graph[i].searched = false;

        // for (int i = 0; i < N; i++) cout << graph[i].goodcycle << endl;

        for (int i = 0; i < N; i++) {
            if (!graph[i].searched) dfsdist(i);
        }

        for (int i = 0; i < N; i++) {
            // if (graph[i].distfromgoodcycle > K - 1) works = false;
            if (graph[i].distfromgoodcycle == 1e18) works = false;
            // cout << graph[i].distfromgoodcycle << endl;
            // cout << graph[i].next << endl;
            if (K == 1 && !graph[i].goodcycle) works = false;
        }

        cout << (works ? "YES" : "NO") << endl;
    }
}