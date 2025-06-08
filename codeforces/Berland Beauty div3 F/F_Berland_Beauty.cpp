// https://codeforces.com/contest/1296/problem/F

// We can sort the passengers from highest minimum to lowest minimum
// Now since N, M <= 1e3, we can perform a dfs over each passenger
// We will set the beauty of each segment a passenger goes over to their minimum beauty
// If that segment hasn't been set already
// Because if that segment has already been set, then that means we can't set the beauty any lower as
// It would make the minimum beauty of another passenger's ride too low
// Any untraversed segments can just be set to a beauty of 1

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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
}; struct passenger {
    int a, b;
    int minbeauty;
}; struct edge {
    int a, b;
    int beauty = -1;
};

vector<node> graph;
vector<edge> edges;

bool works = true;

// first bool is if the path exists, second bool is if you managed to place atleast one of the minimum
pair<bool, bool> dfs(int start, int curidx, int target, int minbeauty) {
    graph[curidx].searched = true;
    if (curidx == target)
        // graph[curidx].beauty = max(graph[curidx].beauty, minbeauty);
        return {true, false};

    for (int next : graph[curidx].next) {
        pair<bool, bool> inpath = {false, false};
        if (!graph[edges[next].a].searched)
            inpath = dfs(start, edges[next].a, target, minbeauty);
        if (!graph[edges[next].b].searched)
            inpath = dfs(start, edges[next].b, target, minbeauty);


        if (inpath.first) {
            // if (edges[next].beauty > -1 && minbeauty < edges[next].beauty) works = false;
            edges[next].beauty = max(edges[next].beauty, minbeauty);
            inpath.second |= edges[next].beauty == minbeauty;

            if (curidx == start && !inpath.second) works = false;
            return inpath;
        }
    }

    // if (inpath) graph[curidx].beauty = max(graph[curidx].beauty, minbeauty);
    return {false, false};
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) graph.push_back({});
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a - 1, b - 1});
        graph[a - 1].next.push_back(i);
        graph[b - 1].next.push_back(i);
    }

    int M;
    cin >> M;
    passenger pass[M];
    for (int i = 0; i < M; i++) {
        cin >> pass[i].a >> pass[i].b >> pass[i].minbeauty;
    }

    sort(pass, pass + M, [](passenger one, passenger two) {
        return one.minbeauty > two.minbeauty;
    });

    for (auto passe : pass) {
        dfs(passe.a - 1, passe.a - 1, passe.b - 1, passe.minbeauty);
        for (int i = 0; i < N; i++) graph[i].searched = false;

        // for (int i = 0; i < N - 1; i++) cout << edges[i].beauty << " ";
        // cout << endl;
    }

    if (!works) cout << -1 << endl;
    else {
        for (int i = 0; i < N - 1; i++) cout << max(edges[i].beauty, 1) << " ";
        cout << endl;
    }
}