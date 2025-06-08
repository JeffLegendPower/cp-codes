// https://codeforces.com/contest/468/problem/B

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

ll a, b;

struct node {
    ll p;
    int nexta = -1, nextb = -1;
    int set = -1;

    bool searched = false;
};
node graph[100001];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> N >> a >> b;

    map<ll, int> pidx;

    for (int i = 0; i < N; i++) {
        cin >> graph[i].p;
        pidx[graph[i].p] = i + 1;

        if (pidx[a - graph[i].p] > 0) {
            graph[i].nexta = pidx[a - graph[i].p] - 1;
            graph[pidx[a - graph[i].p] - 1].nexta = i;
        } if (pidx[b - graph[i].p] > 0) {
            graph[i].nextb = pidx[b - graph[i].p] - 1;
            graph[pidx[b - graph[i].p] - 1].nextb = i;
        }
    }

    // vertices that only have 1 edge
    vector<int> endpoints;

    for (int i = 0; i < N; i++) {
        if (graph[i].nexta != -1 && graph[i].nextb != -1) continue;
        endpoints.push_back(i);
    }
    
    bool works = true;
    while (!endpoints.empty()) {
        int cur = endpoints.back();
        endpoints.pop_back();

        if (graph[cur].searched) continue;

        graph[cur].searched = true;

        int next = graph[cur].nexta;
        if (graph[cur].nextb != -1) {
            int next = graph[cur].nextb;
            graph[cur].set = 1;
            graph[next].set = 1;

            graph[next].searched = true;

            int after = graph[next].nexta;
            if (after != -1) {
                graph[after].nexta = -1;
                endpoints.push_back(after);
            }
        } else if (graph[cur].nexta != -1) {
            int next = graph[cur].nexta;
            graph[cur].set = 0;
            graph[next].set = 0;

            graph[next].searched = true;

            int after = graph[next].nextb;
            if (after != -1) {
                graph[after].nextb = -1;
                endpoints.push_back(after);
            }
        } else works = false;
    }

    for (int i = 0; i < N; i++) {
        if (graph[i].searched) continue;
        graph[i].searched = true;
        graph[i].set = 0;
        graph[graph[i].nexta].searched = true;
        graph[graph[i].nexta].set = 0;
    }

    if (!works) {
        cout << "NO";
        return 0;
    } cout << "YES" << endl;

    for (int i = 0; i < N; i++) cout << graph[i].set << " ";
}