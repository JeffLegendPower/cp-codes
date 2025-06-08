// https://cses.fi/problemset/task/1147

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

    int N, M; cin >> N >> M;

    char grid[N][M];
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> grid[i][j];

    int heights[N][M];
    for (int j = 0; j < M; j++) {
        int height = 0;
        for (int i = N - 1; i >= 0; i--) {
            height++;
            heights[i][j] = height;
            if (grid[i][j] == '*') {
                height = 0;
                heights[i][j] = -1;
            }
        }
    }

    int left[N][M], right[N][M];

    int best = 0;
    for (int i = 0; i < N; i++) {
        stack<int> s1, s2;
        for (int j = 0; j < M; j++) {
            while (!s1.empty() && heights[i][s1.top()] >= heights[i][j]) s1.pop();

            if (s1.empty()) left[i][j] = j;
            else left[i][j] = j - s1.top() - 1;

            s1.push(j);
        }

        for (int j = M - 1; j >= 0; j--) {
            while (!s2.empty() && heights[i][s2.top()] >= heights[i][j]) s2.pop();

            if (s2.empty()) right[i][j] = M - j - 1;
            else right[i][j] = s2.top() - j - 1;

            s2.push(j);

            if (grid[i][j] != '*') {
                best = max(best, (left[i][j] + right[i][j] + 1) * heights[i][j]);
            }
        }
    }

    cout << best;
}