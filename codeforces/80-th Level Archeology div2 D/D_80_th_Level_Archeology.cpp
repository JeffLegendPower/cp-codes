// https://codeforces.com/contest/731/problem/D

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

    int N, C;
    cin >> N >> C;

    vector<vector<int>> wrds;
    for (int i = 0; i < N; i++) {
        int l; cin >> l;
        wrds.push_back({});
        for (int j = 0; j < l; j++) {
            int w; cin >> w;
            w--;
            wrds[i].push_back(w);
        }
    }

    vector<ll> diff(C+1, 0);
    for (int i = 0; i < N - 1; i++) {
        bool same = true;
        for (int j = 0; j < min(wrds[i].size(), wrds[i+1].size()); j++) {
            if (wrds[i][j] == wrds[i+1][j]) continue;
            same = false;

            int a = wrds[i][j], b = wrds[i+1][j];

            if (a < b) {
                diff[0]++;
                diff[C-1-b + 1]--;

                diff[C-a]++;
                diff[C-1 + 1]--;
            } else {
                diff[C-a]++;
                diff[C-1-b + 1]--;
            }

            break;

            // a < b
            // [0, c-1-b] and [c-a, c-1]


            // b < a
            // [c-a, c-1-b]
        }

        if (!same) continue;
        if (wrds[i].size() <= wrds[i+1].size()) {
            diff[0]++;
            diff[C]--;
        }
    }

    int ans = -1;
    for (int i = 0; i <= C; i++) {
        if (i > 0) diff[i] += diff[i-1];
        if (diff[i] == N - 1) ans = i;
    }

    cout << ans;
}