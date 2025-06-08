// https://codeforces.com/contest/1837/problem/E

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

    ll MOD = 998244353;

    int K; cin >> K;
    int N = 1<<K;

    vector<int> a(N, -1);
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        if (x != -1) {
            a[x-1] = i;
        }
    }

    ll ans = 1;
    for (int k = K; k >= 1; k--) {
        vector<bool> used1(1<<(k-1), false);
        ll num1 = 0;
        for (int i = 0; i < 1<<(k-1); i++) {
            if (a[i] == -1) continue;
            if (used1[a[i]>>1]) ans = 0;
            used1[a[i]>>1] = true;
            num1++;
        }

        vector<bool> used2(1<<(k-1), false);
        ll num = 0;
        for (int i = 1<<(k-1); i < 1<<k; i++) {
            if (a[i] != -1) {
                if (used2[a[i]>>1]) ans = 0;
                used2[a[i]>>1] = true;
                if (used1[a[i]>>1]) num1--;
                continue;
            }
            num++;

            ans *= num;
            ans %= MOD;
            if (num > num1) ans *= 2;
            ans %= MOD;
        }
    }

    cout << ans;
}