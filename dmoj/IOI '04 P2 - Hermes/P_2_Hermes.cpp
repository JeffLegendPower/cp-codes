// https://dmoj.ca/problem/ioi04p2

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

    int N; cin >> N;

    pii gods[N];
    for (int i = 0; i < N; i++) cin >> gods[i].first >> gods[i].second;

    ll xdp[2001][2], ydp[2001][2];
    for (int i = -1000; i <= 1000; i++) {
        xdp[i+1000][0] = abs(i) + abs(gods[0].second);
        ydp[i+1000][0] = abs(gods[0].first) + abs(i);
    }

    ll mincost = 1e18;
    for (int i = 1; i < N; i++) {
        int i2 = i&1;
        for (int j = -1000; j <= 1000; j++) {
            xdp[j+1000][i2] = min(
                xdp[j+1000][i2^1] + abs(gods[i].second - gods[i-1].second),
                ydp[gods[i].second+1000][i2^1] + abs(j - gods[i-1].first)
            );

            ydp[j+1000][i2] = min(
                ydp[j+1000][i2^1] + abs(gods[i].first - gods[i-1].first),
                xdp[gods[i].first+1000][i2^1] + abs(j - gods[i-1].second)
            );

            if (i == N-1) mincost = min({mincost, xdp[j+1000][i2], ydp[j+1000][i2]});
        }
    }

    cout << mincost;
}