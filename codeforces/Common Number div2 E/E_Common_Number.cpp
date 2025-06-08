// https://codeforces.com/contest/1271/problem/E

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

ll cnt(ll N, ll x) {
    ll shift = 63 - __builtin_clzll(N) - (63 - __builtin_clzll(x));

    ll y = x << shift;
    ll N2 = N - (N & ((1ll<<(shift)) - 1ll));

    if (y > N2) return (1ll<<(shift)) - 1;
    if (y < N2) return (1ll<<(shift+1)) - 1;
    else return ((1ll<<shift) - 1) + N - y + 1;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll N, k; cin >> N >> k;

    ll low = 0, high = N/2;
    ll best1 = 1;
    while (low <= high) {
        ll mid = low + (high - low) / 2;

        ll x = 2*mid;
        ll num = cnt(N, mid) - 1;
        if (num >= k) {
            low = mid + 1;
            best1 = x;
        } else high = mid - 1;
    }

    low = 0, high = (N-1)/2;
    while (low <= high) {
        ll mid = low + (high - low) / 2;

        ll x = 2*mid+1;
        ll num = cnt(N, x);
        if (num >= k) {
            low = mid + 1;
            best1 = max(best1, x);
        } else high = mid - 1;
    }

    cout << best1;
}