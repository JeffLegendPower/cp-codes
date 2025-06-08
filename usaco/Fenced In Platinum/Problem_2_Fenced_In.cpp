// https://usaco.org/index.php?page=viewproblem2&cpid=625

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("fencedin");

    ll A, B;
    int N, M;
    cin >> A >> B >> N >> M;

    ll verts[N + 2], hors[M + 2];
    verts[0] = 0, verts[N + 1] = A, hors[0] = 0, hors[M + 1] = B;
    for (int i = 1; i <= N; i++) cin >> verts[i];
    for (int i = 1; i <= M; i++) cin >> hors[i];

    sort(verts, verts + N + 2);
    sort(hors, hors + M + 2);

    // x: cost per edge, y: horizontal or vertical (0 = horizontal, 1 = vertical)
    // {x, y}
    vector<plli> edges;
    for (int i = 0; i < N + 2 - 1; i++) {
        edges.push_back({verts[i + 1] - verts[i], 1});
    } for (int i = 0; i < M + 2 - 1; i++) {
        edges.push_back({hors[i + 1] - hors[i], 0});
    }

    sort(edges.begin(), edges.end());

    // whether theres a vertical streak connecting everything
    // whether theres a horizontal streak connecting everything
    bool vertical = false, horizontal = false;
    int numvert = 0, numhor = 0;

    ll cost = 0;
    for (plli edge : edges) {
        ll x = edge.first;
        int type = edge.second;

        if (type == 0) {
            ll num = N;
            if (!horizontal) {
                horizontal = true;
                cost += num * x;
                numhor++;
                continue;
            }

            num -= max(0, numvert - 1);
            
            cost += num * x;
            numhor++;
        } else {
            ll num = M;
            if (!vertical) {
                vertical = true;
                cost += num * x;
                numvert++;
                continue;
            }

            num -= max(0, numhor - 1);
            
            cost += num * x;
            numvert++;
        }
    }

    cout << cost;
}