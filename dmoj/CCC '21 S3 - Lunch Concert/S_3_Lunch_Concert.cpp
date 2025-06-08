// https://dmoj.ca/problem/ccc21s3

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

ll cost(vector<array<ll, 3>> &friends, int N, ll x) {
    ll cost = 0;
    for (int i = 0; i < N; i++) cost += max(0ll, abs(friends[i][0] - x) - friends[i][2]) * friends[i][1];
    return cost;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;

    vector<array<ll, 3>> friends(N);
    for (int i = 0; i < N; i++) cin >> friends[i][0] >> friends[i][1] >> friends[i][2];
    sort(friends.begin(), friends.end());

    // imagine for one friend the function f_i of the time to walk as a function of distance
    // notice that it is convex, which means that it has exactly one minimum
    // and since the sum of convex functions is convex, there is exactly one minimum for the position of the concert
    // making it ternary-searchable
    ll left = 0, right = friends[N - 1][0];
    while (right - left > 2) {
        ll mid1 = left + (right - left) / 3;
        ll mid2 = right - (right - left) / 3;

        if (cost(friends, N, mid1) < cost(friends, N, mid2)) right = mid2;
        else left = mid1;
    }

    ll best = cost(friends, N, left);
    for (ll i = left + 1; i <= right; i++) best = min(best, cost(friends, N, i));

    cout << best;
}