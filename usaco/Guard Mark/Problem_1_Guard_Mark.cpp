// https://usaco.org/index.php?page=viewproblem2&cpid=494

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

struct cw {
    ll h, w, str;  
};

const int MAXN = 20;
ll dp[1<<MAXN]; // max safety factor for cow subset
int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("guard");

    for (int i = 0; i < 1<<MAXN; i++) dp[i] = -1;
    dp[0] = 1e9;

    int N;
    ll H;
    cin >> N >> H;

    cw cows[N];
    for (int i = 0; i < N; i++) cin >> cows[i].h >> cows[i].w >> cows[i].str;

    for (int num = 1; num <= N; num++) {
        for (int msk = 0; msk < 1<<N; msk++) {
            if (__builtin_popcount(msk) != num) continue;

            for (int c = 0; c < N; c++) {
                if (!(msk & (1<<c))) continue;

                dp[msk] = max(dp[msk], min(dp[msk ^ (1<<c)] - cows[c].w, cows[c].str));
            }
        }
    }

    ll best = -1;
    for (int msk = 0; msk < 1<<N; msk++) {
        ll h = 0;
        for (int c = 0; c < N; c++) if (msk & (1<<c)) h += cows[c].h;

        if (h >= H) best = max(best, dp[msk]);
    }

    if (best == -1) cout << "Mark is too tall";
    else cout << best;
}