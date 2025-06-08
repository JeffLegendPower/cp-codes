// https://usaco.org/index.php?page=viewproblem2&cpid=1091

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll N, K, M;
    cin >> N >> K >> M;

    int ends[N];
    vector<array<int, 2>> locs[N];
    for (int i = 0; i < N; i++) {
        ends[i] = i;
        locs[i].push_back({i, 0});
    }

    for (int i = 0; i < K; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        locs[ends[u]].push_back({v, i+1});
        locs[ends[v]].push_back({u, i+1});

        swap(ends[u], ends[v]);
    }

    int edgs[N];
    for (int i = 0; i < N; i++) edgs[ends[i]] = i;
    
    ll jumps = M/K;

    vector<int> ans(N, -1);
    vector<int> cnts(N, 0);

    int num = 0;
    for (int i = 0; i < N; i++) {
        if (ans[i] != -1) continue;

        if (jumps == 0) {
            int j = 0;
            while (j < locs[i].size() && locs[i][j][1] <= M) {
                cnts[locs[i][j][0]]++;
                if (cnts[locs[i][j][0]] == 1) num++;
                j++;
            }

            ans[i] = num;

            j = 0;
            while (j < locs[i].size() && locs[i][j][1] <= M) {
                cnts[locs[i][j][0]]--;
                if (cnts[locs[i][j][0]] == 0) num--;
                j++;
            }

            continue;
        }

        int v = i;
        for (int j = 0; j < jumps; j++) {
            for (auto [x, t] : locs[v]) {
                cnts[x]++;
                if (cnts[x] == 1) num++;
            }

            v = edgs[v];
            if (v == i) break;
        }

        int j = 0;
        while (j < locs[v].size() && locs[v][j][1] <= M%K) {
            cnts[locs[v][j][0]]++;
            if (cnts[locs[v][j][0]] == 1) num++;
            j++;
        }

        ans[i] = num;

        j = 0;
        while (j < locs[v].size() && locs[v][j][1] <= M%K) {
            cnts[locs[v][j][0]]--;
            if (cnts[locs[v][j][0]] == 0) num--;
            j++;
        }

        int v2 = i;
        while (edgs[v2] != i) {
            for (auto [x, t] : locs[v2]) {
                cnts[x]--;
                if (cnts[x] == 0) num--;
            } for (auto [x, t] : locs[v]) {
                cnts[x]++;
                if (cnts[x] == 1) num++;
            }

            v2 = edgs[v2];
            v = edgs[v];

            j = 0;
            while (j < locs[v].size() && locs[v][j][1] <= M%K) {
                cnts[locs[v][j][0]]++;
                if (cnts[locs[v][j][0]] == 1) num++;
                j++;
            }

            ans[v2] = num;

            j = 0;
            while (j < locs[v].size() && locs[v][j][1] <= M%K) {
                cnts[locs[v][j][0]]--;
                if (cnts[locs[v][j][0]] == 0) num--;
                j++;
            }
        }

        for (auto [x, t] : locs[v2]) {
            cnts[x]--;
            if (cnts[x] == 0) num--;
        } for (auto [x, t] : locs[v]) {
            cnts[x]++;
            if (cnts[x] == 1) num++;
        }

        v = i;
        for (int j = 0; j < jumps; j++) {
            for (auto [x, t] : locs[v]) {
                cnts[x]--;
                if (cnts[x] == 0) num--;
            }

            v = edgs[v];
            if (v == i) break;
        }
    }

    for (int i = 0; i < N; i++) cout << ans[i] << endl;
}