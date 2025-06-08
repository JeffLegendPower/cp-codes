// https://usaco.org/index.php?page=viewproblem2&cpid=995

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
const int Nmax = 2e5;  // limit for array size
int N = 2e5;  // array size
ll t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
}

void modify(int p, ll value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 1e18;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(res, t[--r]);
  }
  return res;
}
// Segtree end

struct brd {
    ll x, y;
    int idx;
    bool start;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("boards");

    ll N;
    int P;
    cin >> N >> P;

    brd brds[2*P]; for (int i = 0; i < P; i++) {
        cin >> brds[2*i].x >> brds[2*i].y;
        cin >> brds[2*i+1].x >> brds[2*i+1].y;
        brds[2*i].idx = brds[2*i+1].idx = i;
        brds[2*i].start = true;
        brds[2*i+1].start = false;

        t[200000 + i] = 1e18;
    }

    map<ll, int> ymap;
    sort(brds, brds + 2*P, [](brd one, brd two) {
        return one.y < two.y;
    });

    for (int i = 0; i < 2*P; i++) {
        ymap[brds[i].y] = i;
    }
    sort(brds, brds + 2*P, [](brd one, brd two) {
        if (one.x == two.x) return one.y < two.y;
        return one.x < two.x;
    });

    modify(0, 0);

    ll dp[P];
    ll ans = 2*N;
    for (int i = 0; i < 2*P; i++) {
        if (brds[i].start) {
            dp[brds[i].idx] = query(0, ymap[brds[i].y]+1) + brds[i].x + brds[i].y;
        } else {
            modify(ymap[brds[i].y], dp[brds[i].idx] - brds[i].x - brds[i].y);

            ans = min(ans, dp[brds[i].idx] + (N - brds[i].x) + (N - brds[i].y));
        }
    }

    cout << ans;
}