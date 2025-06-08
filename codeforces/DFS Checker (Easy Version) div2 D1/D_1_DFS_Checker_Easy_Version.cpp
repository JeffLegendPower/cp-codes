// https://mirror.codeforces.com/contest/2002/problem/D1

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
    vector<int> parents;
    int parent;
    int children = 0;
};
vector<node> graph;

vector<int> parents;
void dfs(int curIdx) {
    graph[curIdx].searched = true;

    for (int next : graph[curIdx].next) {
        if (graph[next].searched) continue;
        dfs(next);
        graph[curIdx].children += graph[next].children;
    }
    graph[curIdx].children += graph[curIdx].next.size();
}

bool validate(int i, vector<int> &p) {
    bool sat1 = false, sat2 = false;
    if (graph[p[i]].next.size() == 0) return true;
    if (i + 1 < N) {
        sat1 |= p[i + 1] == graph[p[i]].next[0];
        sat1 |= p[i + 1] == graph[p[i]].next[1];
    }
    if (i + 1 + graph[p[i]].children / 2 < N) {
        sat2 |= p[i + 1 + graph[p[i]].children / 2] == graph[p[i]].next[0];
        sat2 |= p[i + 1 + graph[p[i]].children / 2] == graph[p[i]].next[1];
    }

    return sat1 && sat2;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int Q;
        cin >> N >> Q;
        graph.clear();

        for (int i = 0; i < N; i++) graph.push_back({});

        for (int i = 1; i < N; i++) {
            int a;
            cin >> a;
            graph[a - 1].next.push_back(i);
            graph[i].parent = a - 1;
        }

        vector<int> p(N);
        int idxs[N];
        for (int i = 0; i < N; i++) {
            cin >> p[i];
            p[i]--;
            idxs[p[i]] = i;
        }
        
        dfs(0);

        // child of vertex at idx i must be at
        // i + 1 and (i + 1 + children[vertex] / 2)
        bool satisfied[N];
        for (int i = 0; i < N; i++) satisfied[i] = false;
        int numsatisfied = 0;

        for (int i = 0; i < N; i++) {

            satisfied[p[i]] = validate(i, p);
            if (satisfied[p[i]]) numsatisfied++;
        }

        while (Q--) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;

            int temp = p[x];
            p[x] = p[y];
            p[y] = temp;
            idxs[p[x]] = x;
            idxs[p[y]] = y;

            bool sat = validate(x, p);
            if (sat && !satisfied[p[x]]) numsatisfied++;
            else if (!sat && satisfied[p[x]]) numsatisfied--;
            satisfied[p[x]] = sat;

            sat = validate(y, p);
            if (sat && !satisfied[p[y]]) numsatisfied++;
            else if (!sat && satisfied[p[y]]) numsatisfied--;
            satisfied[p[y]] = sat;

            int px = graph[p[x]].parent;
            sat = validate(idxs[px], p);
            if (sat && !satisfied[px]) numsatisfied++;
            else if (!sat && satisfied[px]) numsatisfied--;
            satisfied[px] = sat;

            int py = graph[p[y]].parent;
            sat = validate(idxs[py], p);
            if (sat && !satisfied[py]) numsatisfied++;
            else if (!sat && satisfied[py]) numsatisfied--;
            satisfied[py] = sat;

            if (numsatisfied == N) cout << "YES";
            else cout << "NO";
            cout << endl;
        }
    }
}