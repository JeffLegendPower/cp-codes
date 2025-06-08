// https://usaco.org/index.php?page=viewproblem2&cpid=600

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

    setIO("fortmoo");

    int N, M;
    cin >> N >> M;

    bool grid[N][M];
    int pre[N+1][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c; cin >> c;
            grid[i][j] = c == 'X';
            pre[i+1][j] = grid[i][j];
        }
    }

    for (int j = 0; j < M; j++) pre[0][j] = 0;

    for (int j = 0; j < M; j++) {
        for (int i = 1; i <= N; i++) {
            pre[i][j] += pre[i-1][j];
        }
    }

    int best = 0;
    for (int i1 = 0; i1 < N; i1++) {
        for (int i2 = i1; i2 < N; i2++) {
            int mincol = -1;
            for (int j = 0; j < M; j++) {
                if (grid[i1][j] || grid[i2][j]) {
                    mincol = -1;
                    continue;
                }

                if (pre[i2+1][j] - pre[i1][j]) continue;

                if (mincol == -1) {
                    mincol = j;
                    continue;
                }

                best = max(best, (j-mincol+1)*(i2-i1+1));
            }
        }
    }

    cout << best;
}