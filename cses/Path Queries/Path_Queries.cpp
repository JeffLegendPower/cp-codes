// https://cses.fi/problemset/task/1138

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
const int Nmax = 2e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

ll oper(ll a, ll b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
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
    ll val;

    int start = -1, end = -1;
};
node graph[200000];

int timer = 0;
void euler_tour(int cur, int parent) {
    graph[cur].start = timer++;

    for (int next : graph[cur].next) {
        if (next == parent) continue;

        euler_tour(next, cur);
    }

    graph[cur].end = timer;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int Q;
    cin >> N >> Q;

    for (int i = 0; i < N; i++) cin >> graph[i].val;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].next.push_back(b);
        graph[b].next.push_back(a);
    }
    euler_tour(0, -1);

    // for (int i = 0; i < N; i++) t[N + graph[i].start] = graph[i].val;
    for (int i = 0; i < N; i++) {
        modify(graph[i].start, graph[i].end, graph[i].val);
    }

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int s;
            ll x;
            cin >> s >> x;
            s--;

            modify(graph[s].start, graph[s].end, x - graph[s].val);
            graph[s].val = x;
        } else if (t == 2) {
            int s;
            cin >> s;
            s--;

            cout << query(graph[s].start) << endl;
        }
    }
}