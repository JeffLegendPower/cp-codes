// https://codeforces.com/problemset/problem/1722/F

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

bool grid[100][100];

bool testL(int i, int j, int l, int N, int M) {
    bool works = true;

    if (i>1) {
        if (grid[i-2][j]|grid[i-2][j-1]) works = false;
    } if (i<N-1) {
        if (grid[i+1][j]|grid[i+1][j-1]) works = false;
    } if (j>1) {
        if (grid[i][j-2]|grid[i-1][j-2]) works = false;
    } if (j<M-1) {
        if (grid[i][j+1]|grid[i-1][j+1]) works = false;
    }

    if (l != 0 && i>1 && j<M-1 && grid[i-2][j+1]) works = false;
    if (l != 1 && i>1 && j>1 && grid[i-2][j-2]) works = false;
    if (l != 2 && i<N-1 && j>1 && grid[i+1][j-2]) works = false;
    if (l != 3 && i<N-1 && j<M-1 && grid[i+1][j+1]) works = false;

    return works;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;

        for (int i = 0; i < N; i++) {
            string s; cin >> s;
            for (int j = 0; j < M; j++) {
                grid[i][j] = s[j] == '*';
            }
        }

        bool works = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!grid[i][j]) continue;
                int l = -1;
                int i2, j2;
                if (i>0 && j<M-1) {
                    if (grid[i-1][j]&grid[i][j+1]) {
                        l = 0;
                        i2 = i;
                        j2 = j+1;
                        grid[i][j] = false;
                        grid[i-1][j] = false;
                        grid[i][j+1] = false;

                        if (grid[i-1][j+1]) works = false;
                    }
                } if (i>0 && j>0) {
                    if (grid[i-1][j]&grid[i][j-1]) {
                        l = 1;
                        i2 = i;
                        j2 = j;
                        grid[i][j] = false;
                        grid[i-1][j] = false;
                        grid[i][j-1] = false;

                        if (grid[i-1][j-1]) works = false;
                    }
                } if (i<N-1 && j>0) {
                    if (grid[i][j-1]&grid[i+1][j]) {
                        l = 2;
                        i2 = i+1;
                        j2 = j-1;
                        grid[i][j] = false;
                        grid[i][j-1] = false;
                        grid[i+1][j] = false;

                        if (grid[i+1][j-1]) works = false;
                    }
                } if (i<N-1 && j<M-1) {
                    if (grid[i][j+1]&grid[i+1][j]) {
                        l = 3;
                        i2 = i+1;
                        j2 = j+1;
                        grid[i][j] = false;
                        grid[i][j+1] = false;
                        grid[i+1][j] = false;

                        if (grid[i+1][j+1]) works = false;
                    }
                }

                if (l == -1) continue;
                if (!testL(i2, j2, l, N, M)) works = false;
            }
        }

        for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) if (grid[i][j]) works = false;

        cout << (works ? "YES" : "NO") << endl;
    }
}