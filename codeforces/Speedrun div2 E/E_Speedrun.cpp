// https://codeforces.com/problemset/problem/1863/E

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
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
    vector<int> prev;
    ll h;
    ll day = 0;

    // min hr offset until quest completion day is shifted 1 day to the right (after atleast 1 more hr shift)
    ll shift;
};
vector<node> graph;

void dfs(int cur) {
    if (graph[cur].prev.size() > 0) graph[cur].shift = 1e12;

    for (int prev : graph[cur].prev) {
        dfs(prev);
        if (graph[prev].h <= graph[cur].h) graph[cur].day = max(graph[cur].day, graph[prev].day);
        else graph[cur].day = max(graph[cur].day, graph[prev].day + 1);
    }

    for (int prev : graph[cur].prev) {
        if (graph[prev].h <= graph[cur].h) {
            if (graph[prev].day == graph[cur].day) graph[cur].shift = min(graph[cur].shift, graph[prev].shift);
        } else if (graph[prev].day + 1 == graph[cur].day) graph[cur].shift = min(graph[cur].shift, graph[prev].shift);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        ll K;
        cin >> N >> M >> K;

        graph.clear();
        for (int i = 0; i < N; i++) {
            node cur; cin >> cur.h;
            cur.shift = cur.h;
            graph.push_back(cur);
        }

        for (int i = 0; i < M; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            graph[b].prev.push_back(a);
        }

        ll end = 0;
        for (int i = 0; i < N; i++) {
            dfs(i);
            end = max(end, graph[i].h + K * graph[i].day);
        }

        sort(graph.begin(), graph.end(), [](node one, node two) {
            return one.shift < two.shift;
        });

        ll best = end - graph[0].h;
        for (int i = 0; i < N - 1; i++) {
            end = max(end, graph[i].h + K * (graph[i].day + 1));
            if (graph[i].shift == graph[i + 1].shift) continue;

            best = min(best, end - graph[i + 1].h);
        }

        cout << best << endl;
    }
}