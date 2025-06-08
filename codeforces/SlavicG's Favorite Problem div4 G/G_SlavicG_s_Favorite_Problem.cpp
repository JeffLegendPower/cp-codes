// https://codeforces.com/contest/1760/problem/G

// We can solve this problem by knowing all the xors from any vertex to b
// and the xors from any vertex to a
// if the xor from a to b is 0, then it's obviously possible to go from a to b
// otherwise, we need to find all the vertices a can go to and store the xor to them
// (note that we can't go to b or past it so we must account for it)
// Now, we just store the xors from all nodes to b in a set, and see if an xor from a to reachable node
// is equal to it. If so, then it's possible
// Otherwise, impossible

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
typedef pair<int, int> pii;

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
    ll xorB = 1e18;
    ll xorA = 1e18;
};

vector<node> graph;
int a, b;

// Get the XOR of all the w's going from each vertex to vertex b
// this can be done in O(N) time by going outwards from vertex b
// as there is only 1 path to each other vertex (undirected acyclic graph)
void dfsB(int curIdx, ll curXor) {
    graph[curIdx].searched = true;
    // if (graph[curIdx].xorB > -1) return graph[curIdx].xorB;
    graph[curIdx].xorB = curXor;

    // xeor = xeor ^ 0;

    for (plli next : graph[curIdx].next) {
        if (graph[next.second].searched) continue;
        dfsB(next.second, curXor ^ next.first);
    }
}

// Now do the same for a
void dfsA(int curIdx, ll curXor) {
    graph[curIdx].searched = true;
    if (curIdx == b - 1) return;
    graph[curIdx].xorA = curXor;

    for (plli next : graph[curIdx].next) {
        if (graph[next.second].searched) continue;
        dfsA(next.second, curXor ^ next.first);
    }
}


int main() {
    int T;
    cin >> T;

    while (T--) {
        cin >> N >> a >> b;

        graph.clear();

        for (int i = 0; i < N; i++) graph.push_back({});

        for (int i = 0; i < N - 1; i++) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            graph[u - 1].next.push_back({w, v - 1});
            graph[v - 1].next.push_back({w, u - 1});
        }

        dfsB(b - 1, 0);
        
        set<ll> xorB;
        // Account for the case where we can just take the path from a to b
        bool works = graph[a - 1].xorB == 0;

        for (int i = 0; i < N; i++) {
            graph[i].searched = false;
            if (i != b - 1) xorB.insert(graph[i].xorB);
        }
        
        dfsA(a - 1, 0);

        for (int i = 0; i < N; i++) {
            if (i != b - 1)
                if (xorB.find(graph[i].xorA) != xorB.end()) works = true;
        }

        cout << (works ? "YES" : "NO") << endl;
    }
}