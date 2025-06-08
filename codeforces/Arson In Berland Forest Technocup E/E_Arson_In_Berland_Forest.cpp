// https://codeforces.com/contest/1227/problem/E

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

int presum(int i1, int j1, int i2, int j2, vector<vector<int>> &pre) {
    return pre[i2+1][j2+1] - pre[i1][j2+1] - pre[i2+1][j1] + pre[i1][j1];
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> pre(N+1, vector<int>(M+1));

    for (int i = 0; i <= N; i++) pre[i][0] = 0;
    for (int i = 0; i <= M; i++) pre[0][i] = 0;

    char input[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c; cin >> c;
            input[i][j] = c;
            pre[i+1][j+1] = pre[i+1][j] + pre[i][j+1] - pre[i][j] + (c == 'X');
        }
    }

    int low = 0, high = min(N, M);
    int best = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        vector<vector<int>> pre2(N+1, vector<int>(M+1));
        for (int i = 0; i <= N; i++) pre2[i][0] = 0;
        for (int i = 0; i <= M; i++) pre2[0][i] = 0;

        for (int i = mid; i < N - mid; i++) {
            for (int j = mid; j < M - mid; j++) {
                if (presum(i-mid, j-mid, i+mid, j+mid, pre) == (2*mid+1)*(2*mid+1)) {
                    pre2[i+1][j+1]++;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                pre2[i+1][j+1] += pre2[i+1][j] + pre2[i][j+1] - pre2[i][j];
            }
        }

        bool works = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (input[i][j] == '.') continue;
                if (presum(max(0, i-mid), max(0, j-mid), min(N-1, i+mid), min(M-1, j+mid), pre2) == 0) {
                    works = false;
                }
            }
        }

        if (works) {
            low = mid + 1;
            best = mid;
        } else high = mid - 1;
    }

    char grid[N][M];
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) grid[i][j] = '.';

    for (int i = best; i < N - best; i++) {
        for (int j = best; j < M - best; j++) {
            if (presum(i-best, j-best, i+best, j+best, pre) == (2*best+1)*(2*best+1)) {
                grid[i][j] = 'X';
            }
        }
    }

    cout << best << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cout << grid[i][j];
        cout << endl;
    }
}