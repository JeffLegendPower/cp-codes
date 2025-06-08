// https://usaco.org/index.php?page=viewproblem2&cpid=1305&lang=en

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

struct rnge {
    int a, b;
    ll sum;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;

    ll a[N], pre[N + 1];
    pre[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        pre[i + 1] = pre[i] + a[i];
    }

    ll ans[N];

    vector<array<ll, 3>> subarrs;
    for (int i = 0; i < N; i++) for (int j = i; j < N; j++) subarrs.push_back({i, j, pre[j + 1] - pre[i]});
    sort(subarrs.begin(), subarrs.end(), [](array<ll, 3> one, array<ll, 3> two) {
        return one[2] < two[2];
    });

    for (int i = 0; i < N; i++) {
        ans[i] = 1e18;
        for (int j = 0; j < subarrs.size(); j++) {
            if (subarrs[j][0] > i || i > subarrs[j][1]) continue;
            if (j > 0 && (subarrs[j - 1][0] > i || subarrs[j - 1][1] < i)) {
                ans[i] = min(ans[i], subarrs[j][2] - subarrs[j - 1][2]);
            } if (j < subarrs.size() - 1 && (subarrs[j + 1][0] > i || subarrs[j + 1][1] < i)) {
                ans[i] = min(ans[i], subarrs[j + 1][2] - subarrs[j][2]);
            }
        }
    }

    for (int i = 0; i < N; i++) cout << ans[i] << endl;
}