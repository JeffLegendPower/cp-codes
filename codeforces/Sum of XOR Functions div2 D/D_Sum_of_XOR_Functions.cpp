// https://codeforces.com/problemset/problem/1879/D

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
    ll a[N]; for (int i = 0; i < N; i++) cin >> a[i];

    ll MOD = 998244353;

    ll ans = 0;
    for (ll b = 0; b <= 0; b++) {

        vector<ll> bounds;
        for (int i = 0; i < N; i++) {
            // cout << a[i] << " " << (1<<b) << endl;
            if ((a[i]&(1ll<<b)) > 0) {
                bounds.push_back(i);
            }
        }

        vector<plli> idxs;
        int bound = 0;
        ll evensum = 0, oddsum = 0;
        int evens = 0, odds = 0;
        for (ll i = 0; i < N; i++) {
            if (bound < bounds.size() && bounds[bound] == i) bound++;
            idxs.push_back({i, bound&1});
            if (bound&1) {
                oddsum += i + 1;
                odds++;
            } else {
                evensum += i + 1;
                evens++;
            }
        }

        for (int j = 0; j < idxs.size(); j++) {
            auto [i, sign] = idxs[j];
            cout << i << " " << sign << endl;
            
            ll addd;
            if (sign) addd = evensum - i * evens;
            else addd = oddsum - i * odds;

            addd = (addd * (1<<b)) % MOD;
            ans = (ans + addd) % MOD;

            if (sign) {
                oddsum -= i + 1;
                odds--;
            } else {
                evensum -= i + 1;
                evens--;
            }
        }
    }

    cout << ans;
}