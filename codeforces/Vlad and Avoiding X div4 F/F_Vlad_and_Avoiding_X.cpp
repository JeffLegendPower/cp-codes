// https://codeforces.com/problemset/problem/1926/F

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

ll bad1 = 0, bad2 = 0;
bool grid[7][7];
bool bads[7][7];
vector<pii> black1, black2;

ll min1 = 1e6, min2 = 1e6;

void dfs(int x, ll t, int type) {
    int red = 0;
    vector<pii> reds;

    int i, j;
    if (type == 1) {
        i = black1[x].first;
        j = black1[x].second;
    } else {
        i = black2[x].first;
        j = black2[x].second;
    }

    if (bads[i][j]) {
        red++;
        reds.push_back({i, j});
        bads[i][j] = false;
    } if (min(i, j) > 0 && bads[i - 1][j - 1]) {
        red++;
        reds.push_back({i - 1, j - 1});
        bads[i - 1][j - 1] = false;
    } if (max(i, j) < 6 && bads[i + 1][j + 1]) {
        red++;
        reds.push_back({i + 1, j + 1});
        bads[i + 1][j + 1] = false;
    } if (i > 0 && j < 6 && bads[i - 1][j + 1]) {
        red++;
        reds.push_back({i - 1, j + 1});
        bads[i - 1][j + 1] = false;
    } if (i < 6 && j > 0 && bads[i + 1][j - 1]) {
        red++;
        reds.push_back({i + 1, j - 1});
        bads[i + 1][j - 1] = false;
    }


    if (type == 1) bad1 -= red;
    else bad2 -= red;

    if ((type == 1 && bad1 == 0) || (type == 2 && bad2 == 0)) {
        if (type == 1) min1 = min(min1, t);
        else min2 = min(min2, t);
    }

    if (t < 4) {
        for (int j = x + 1; j < (type == 1 ? black1.size() : black2.size()); j++) {
            dfs(j, t + 1, type);
        }
    }

    if (type == 1) bad1 += red;
    else bad2 += red;
    for (auto [i1, j1] : reds) bads[i1][j1] = true;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        bad1 = 0;
        bad2 = 0;
        min1 = 1e6, min2 = 1e6;
        black1.clear();
        black2.clear();

        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                char c; cin >> c;
                grid[i][j] = c == 'B';
                bads[i][j] = false;
                if (grid[i][j]) {
                    if ((i + j)&1) black2.push_back({i, j});
                    else black1.push_back({i, j});
                }
            }
        } for (int i = 1; i < 6; i++) {
            for (int j = 1; j < 6; j++) {
                if (grid[i][j] && grid[i + 1][j + 1] && grid[i + 1][j - 1] && grid[i - 1][j + 1] && grid[i - 1][j - 1]) {
                    if ((i + j)&1) bad2++;
                    else bad1++;
                    bads[i][j] = true;
                }
            }
        }

        if (bad1 == 0) min1 = 0;
        if (bad2 == 0) min2 = 0;

        for (int i = 0; i < black1.size(); i++) dfs(i, 1, 1);
        for (int i = 0; i < black2.size(); i++) dfs(i, 1, 2);

        cout << min1 + min2 << endl;
    }
}