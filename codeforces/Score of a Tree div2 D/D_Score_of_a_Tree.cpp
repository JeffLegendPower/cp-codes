// https://codeforces.com/contest/1777/problem/D

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

ll MOD = 1e9 + 7;

struct node {
    bool searched = false;
    vector<int> next;
    ll dpval = 0;
};
vector<node> graph;
vector<int> numheight;

void dfs(int cur, int depth) {
    graph[cur].searched = true;
    if (numheight.size() == depth) numheight.push_back(0);
    numheight[depth]++;

    for (int next : graph[cur].next) {
        if (graph[next].searched) continue;
        dfs(next, depth + 1);
    }
}

ll binpow(ll a, ll b, ll MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    int T;
    cin >> T;

    ll MOD = 1e9 + 7;

    while (T--) {
        int N;
        cin >> N;
        graph.clear();
        numheight.clear();

        for (int i = 0; i < N; i++) graph.push_back({});
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            graph[u - 1].next.push_back(v - 1);
            graph[v - 1].next.push_back(u - 1);
        }

        dfs(0, 0);

        ll pres[numheight.size() + 1];
        pres[numheight.size()] = 1;
        pres[numheight.size() - 1] = binpow(2, numheight.back() - 1, MOD);
        for (int i = numheight.size() - 2; i >= 0; i--) {
            pres[i] = (pres[i + 1] + binpow(2, numheight[i] - 1, MOD)) % MOD;
        }

        ll total = 0;
        for (int i = numheight.size() - 1; i >= 0; i--) {
            ll diff = (numheight[i] * binpow(2, numheight[i] - 1, MOD)) % MOD;
            diff = (diff * pres[i + 1]) % MOD;
            total += diff;
        }

        cout << total << endl;
    }
}