// https://codeforces.com/contest/2007/problem/D

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
    char c;
    ll score = 0;
};
vector<node> graph;

vector<int> leaves;
int nonleafunk = 0;
void dfs(int curIdx) {
    graph[curIdx].searched = true;

    bool hasnext = false;
    for (int next : graph[curIdx].next) {
        if (graph[next].searched) continue;
        hasnext = true;
        dfs(next);
    }

    if (!hasnext) leaves.push_back(curIdx);
    else if (graph[curIdx].c == '?') nonleafunk++;
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
        graph.clear();
        leaves.clear();
        nonleafunk = 0;

        for (int i = 0; i < N; i++) {
            graph.push_back({});
        }

        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            graph[u - 1].next.push_back(v - 1);
            graph[v - 1].next.push_back(u - 1);
        }
        for (int i = 0; i < N; i++) {
            cin >> graph[i].c;
        }

        dfs(0);

        int leaf1 = 0, leaf0 = 0, leafunk = 0;

        for (int leaf : leaves) {
            if (graph[leaf].c == '1') leaf1++;
            else if (graph[leaf].c == '0') leaf0++;
            else leafunk++;
        }

        if (graph[0].c == '?') nonleafunk--;

        int score2 = 0;
        if (nonleafunk % 2 == 1 && leaf1 == leaf0 && graph[0].c == '?') {
            bool iris = false;
            score2 = leaf1 + (leafunk + 1) / 2;
        }

        bool iris = true;
        int score = 0;
        if (graph[0].c == '?') {
            iris = false;
            if (leaf1 > leaf0) {
                graph[0].c = '0';
                score += leaf1;
            } else {
                score += leaf0;
                graph[0].c = '1';
            }
        } else if (graph[0].c == '1') {
            score += leaf0;
        } else score += leaf1;

        if (iris) {
            score += (leafunk + 1) / 2;
        } else score += leafunk / 2;

        cout << max(score, score2) << endl;
    }
}