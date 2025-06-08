// https://usaco.org/index.php?page=viewproblem2&cpid=1354&lang=en

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

#define piis pair<int, string>

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct etry {
    int i;
    ll l;
    int previdx;
};
struct comp {
    bool operator() (const etry& a, const etry& b) const {
        if (a.l < b.l) return true;
        else if (b.l < a.l) return false;
        else if (a.previdx < b.previdx) return true;
        else return a.i < b.i;
    }
};

typedef tree<etry, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


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
    vector<plli> next;

    bool searched = false;

    int len = 0;
    ll labelsum = 0;
    vector<ll> labels;

    int sortidx = -1;
};
node graph[200000];
ordered_multiset osets[200001];

void dfs(int cur) {
    graph[cur].searched = true;
    for (auto [l, next] : graph[cur].next) {
        if (!graph[next].searched) dfs(next);
        graph[cur].len = max(graph[cur].len, graph[next].len + 1);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int u, v;
        ll l;
        cin >> u >> v >> l;
        graph[u - 1].next.push_back({l, v - 1});
    } for (int i = 0; i < N; i++) {
        sort(graph[i].next.begin(), graph[i].next.end());
    }

    vector<int> idxs[200001];
    for (int i = 0; i < N; i++) {
        if (!graph[i].searched) dfs(i);
        idxs[graph[i].len].push_back(i);
    }

    for (int len = 0; len < 200001; len++) {
        for (int v : idxs[len]) {
            ll lf = 1e18;
            int bnext = -1;
            int bnextidx = 1e6;
            for (auto [l, next] : graph[v].next) {
                if (graph[next].len < len - 1) continue;
                if (l > lf) continue;
                if (l < lf) {
                    lf = l;
                    bnext = next;
                    bnextidx = graph[next].sortidx;
                    graph[v].labelsum = graph[next].labelsum + l;
                    continue;
                }

                int nextidx = graph[next].sortidx;
                if (nextidx < bnextidx) {
                    bnext = next;
                    bnextidx = nextidx;
                    graph[v].labelsum = graph[next].labelsum + l;
                }
            }
            osets[len].insert({v, lf, bnextidx});
        } 
        
        int i = -1;
        for (auto itr = osets[len].begin(); itr != osets[len].end(); itr++) {
            i++;
            graph[itr->i].sortidx = i;
        }
    }

    for (int i = 0; i < N; i++) cout << graph[i].len << " " << graph[i].labelsum << endl;
}