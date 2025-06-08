// https://codeforces.com/contest/1891/problem/F

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
const int Nmax = 1e6;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

void build() {  // build the tree
    for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int l, int r, ll value) {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l&1) t[l++] += value;
        if (r&1) t[--r] += value;
    }
}

ll query(int p) {
    ll res = 0;
    for (p += N; p > 0; p >>= 1) res += t[p];
    return res;
}
// Segtree end


struct node {
    vector<int> next;
    int arridx;

    int numchildren = 1;
};
vector<node> graph;
struct qry {
    int t; // type of query
    int a; // if t=1, then this is the parent to attach v to, if t=2, then this is the vertex whose subtree to update
    ll b; // if t=1, then this is the vertex v to be attached to the parent, if t=2, then this is the value to be incremented
};

int arridx;
void dfs(int graphidx) {
    graph[graphidx].arridx = arridx++;
    for (int next : graph[graphidx].next) {
        dfs(next);
        graph[graphidx].numchildren += graph[next].numchildren;
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int Q;
        cin >> Q;
        graph.clear();
        graph.push_back({});

        vector<qry> queries;
        for (int i = 0; i < Q; i++) {
            qry cur;
            cin >> cur.t >> cur.a;
            cur.a--;

            if (cur.t == 2) cin >> cur.b;
            else {
                node nod;
                graph.push_back(nod);
                graph[cur.a].next.push_back(graph.size() - 1);
                cur.b = graph.size() - 1;
            }

            queries.push_back(cur);
        }

        arridx = 0;
        dfs(0);
        N = graph.size();
        for (int i = 0; i < N; i++) t[N + i] = 0;
        build();

        for (int i = 0; i < Q; i++) {
            qry cur = queries[i];
            if (cur.t == 1) {
                modify(
                    graph[cur.b].arridx, 
                    graph[cur.b].arridx + graph[cur.b].numchildren, 
                    -query(graph[cur.a].arridx)
                );
            } else {

                modify(
                    graph[cur.a].arridx,
                    graph[cur.a].arridx + graph[cur.a].numchildren,
                    cur.b
                );
            }
        }

        for (int i = 0; i < N; i++) {
            cout << query(graph[i].arridx) << " ";
        }
        cout << endl;
    }
}