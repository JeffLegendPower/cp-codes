// https://codeforces.com/contest/1790/problem/G

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
    bool searched = false;
    bool token, bonus;
    vector<int> next;
};

int reqdist = 1e6;
int usingtoken = -1;
vector<node> graph;

void dfs1(int curIdx, int dist) {
    graph[curIdx].searched = true;
    if (graph[curIdx].token && dist - 1 < reqdist) {
        // works = true;
        reqdist = dist - 1;
        usingtoken = curIdx;
        return;
    } if (graph[curIdx].bonus || curIdx == 0) {
        for (int next : graph[curIdx].next) {
            if (graph[next].searched) continue;
            dfs1(next, dist + 1);
        }
    }
}

int num1 = 0;
bool is2 = false;
int dfs2(int curIdx) {
    graph[curIdx].searched = true;
    int maxdist = 0;
    bool has1 = false;
    for (int next : graph[curIdx].next) {
        if (graph[next].bonus) {
            if (graph[curIdx].token)
                has1 = true;
            if (graph[next].searched) continue;
            maxdist = max(dfs2(next), maxdist);
        }
    }
    num1 += has1;
    if (graph[curIdx].bonus) maxdist++;
    if (maxdist >= 2) is2 = true;
    return maxdist;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, M;
        int p, b;
        cin >> N >> M >> p >> b;
        graph.clear();
        num1 = 0;
        is2 = false;
        // works = false;

        for (int i = 0; i < N; i++) graph.push_back({});
        for (int i = 0; i < p; i++) {
            int idx;
            cin >> idx;
            graph[idx - 1].token = true;
        } for (int i = 0; i < b; i++) {
            int idx;
            cin >> idx;
            graph[idx - 1].bonus = true;
        } for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            graph[u - 1].next.push_back(v - 1);
            graph[v - 1].next.push_back(u - 1);
        }

        dfs1(0, 0);
        if (reqdist == 1e6) {
            cout << "NO" << endl;
            continue;
        } if (reqdist <= 0) {
            cout << "YES" << endl;
            continue;
        }
        for (int i = 0; i < N; i++) graph[i].searched = false;
        for (int i = 0; i < N; i++) {
            if (i == usingtoken) continue;
            if (graph[i].token) dfs2(i);
        }
        if (reqdist <= num1 || is2) cout << "YES" << endl;
        else cout << "NO" << endl;
        // cout << (works ? "YES" : "NO") << endl;
        // cout << reqdist << endl;
        cout << num1 << " " << is2 << endl;
    }
}