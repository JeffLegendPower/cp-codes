// https://codeforces.com/problemset/problem/1931/F

// This problem is giving us a bunch of comparisons between some numbers
// and is asking us if there exists a contradiction between them (if yes then answer is NO)
// If we represent these numbers as vertices in a graph and comparisons as directed edges
// Then the graph should be 1 or more chains if there exists no contradictions
// Otherwise, a cycle would exist in the graph
// So, if we represent the problem as a graph and look for a cycle, we can determine the answer
// If a cycle exists, the answer is NO, otherwise the answer is YES

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
    vector<int> next;
};
vector<node> graph;
vector<bool> recursionstack;

bool iscyclic(int curIdx) {
    graph[curIdx].searched = true;
    for (int next : graph[curIdx].next) {
        if (recursionstack[next]) return true;
        if (graph[next].searched) continue;
        recursionstack[next] = true;
        bool res = iscyclic(next);
        recursionstack[next] = false;

        if (res) return true;
    }

    return false;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, k;
        cin >> N >> k;

        graph.clear();
        recursionstack.clear();

        for (int i = 0; i < N; i++) {
            graph.push_back({});
            recursionstack.push_back(false);
        } for (int i = 0; i < k; i++) {
            vector<int> compares;
            for (int i = 0; i < N; i++) {
                int ai;
                cin >> ai;
                compares.push_back(ai);
            }
            for (int i = 2; i < compares.size(); i++) {
                graph[compares[i - 1] - 1].next.push_back(compares[i] - 1);
            }
        }

        bool cyclic = false;
        for (int i = 0; i < N; i++) {
            if (!graph[i].searched) {
                recursionstack[i] = true;
                cyclic |= iscyclic(i);
                recursionstack[i] = false;
            }
        }

        cout << (cyclic ? "NO" : "YES") << endl;
    }
}