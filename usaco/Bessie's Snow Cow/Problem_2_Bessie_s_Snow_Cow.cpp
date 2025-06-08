// https://usaco.org/index.php?page=viewproblem2&cpid=973

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
    bool operator() (const pii& a, const pii& b) const {
        return a < b;
    }
};

typedef tree<pii, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 1e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

int h;
ll d[Nmax];

void calc(int p, ll k) {
    t[p] = t[p<<1] + t[p<<1|1] + d[p] * k;
}

void apply(int p, ll value, ll k) {
  t[p] += value * k;
  if (p < N) d[p] += value;
}

void build(int l, int r) {
  ll k = 2;
  for (l += N, r += N-1; l > 1; k <<= 1) {
    l >>= 1, r >>= 1;
    for (int i = r; i >= l; --i) calc(i, k);
  }
}

void push(int l, int r) {
  int s = h, k = 1 << (h-1);
  for (l += N, r += N-1; s > 0; --s, k >>= 1)
    for (int i = l >> s; i <= r >> s; ++i) if (d[i] != 0) {
      apply(i<<1, d[i], k);
      apply(i<<1|1, d[i], k);
      d[i] = 0;
    }
}

void modify(int l, int r, ll value) {
  if (value == 0) return;
  push(l, l + 1);
  push(r - 1, r);
  int l0 = l, r0 = r, k = 1;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1, k <<= 1) {
    if (l&1) apply(l++, value, k);
    if (r&1) apply(--r, value, k);
  }
  build(l0, l0 + 1);
  build(r0 - 1, r0);
}

ll query(int l, int r) {
  push(l, l + 1);
  push(r - 1, r);
  ll res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}

// Segtree end

struct node {
    vector<int> next;

    int start, end;
};
node graph[Nmax];

int timer = 0;
void euler_tour(int cur, int parent) {
    graph[cur].start = timer++;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur);
    }

    graph[cur].end = timer;
}

set<pii> opers[100000];
set<pii, greater<pii>> opers2[100000];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("snowcow");

    int Q;
    cin >> N >> Q;

    h = sizeof(int) * 8 - __builtin_clz(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }
    euler_tour(0, -1);

    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, c;
            cin >> x >> c;
            x--, c--;

            int start = graph[x].start, end = graph[x].end;
            auto itr2 = opers2[c].lower_bound({start, x});
            if (itr2 != opers2[c].end()) {
                int u = itr2->second;
                // cout << "J" << " " << graph[u].end << " " << graph[x].end << endl;
                if (graph[u].end >= end) {
                    // cout << "E" << endl;
                    continue;
                }
            }

            while (true) {
                auto itr = opers[c].lower_bound({start, x});
                if (itr == opers[c].end()) break;
                auto [startu, u] = *itr;

                if (startu >= end) break;
                opers[c].erase({startu, u});
                opers2[c].erase({startu, u});

                modify(graph[u].start, graph[u].end, -1);
            }

            // cout << x << " " << start << " " << end << endl;
            // cout << query(graph[1].start, graph[1].end) << endl;

            // cout << x << " " << graph[x].start << " " << graph[x].end << endl;
            // cout << start << " " << end << endl;


            modify(start, end, 1);
            // cout << query(4, 5) << endl;
            // cout << query(graph[1].start, graph[1].end) << " E" << endl;
            opers[c].insert({start, x});
            opers2[c].insert({start, x});

            // cout << endl;
        } else if (t == 2) {
            int x;
            cin >> x;
            x--;
            
            // cout << graph[x].start << " " << graph[x].end << endl;
            cout << query(graph[x].start, graph[x].end) << endl;
        }
    }
}