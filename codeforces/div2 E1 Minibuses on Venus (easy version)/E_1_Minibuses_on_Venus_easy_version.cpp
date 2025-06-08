// https://codeforces.com/contest/1808/problem/E1

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

ll binpow(ll a, ll b, ll MOD) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, K;
    ll MOD; cin >> N >> K >> MOD;

    vector<ll> ways(N*(K-1) + 1, 0);
    ways[0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = N*(K-1); j >= 0; j--) {
            ll num = 0;
            for (int k = 0; k < min(K, j+1); k++) {
                num += ways[j-k];
                num %= MOD;
            }

            ways[j] = num;
        }
    }

    vector<vector<ll>> ways2(K, vector<ll>(N*(K-1) + 1));
    for (int modd = 0; modd < K; modd++) {
        ways2[modd][0] = 1;
        for (int i = 0; i < N; i++) {
            for (int j = N*(K-1); j >= 0; j--) {
                ll num = 0;
                for (int k = 0; k < min(K, j+1); k++) {
                    if ((2*k)%K == modd) continue;
                    num += ways2[modd][j-k];
                    num %= MOD;
                }
                ways2[modd][j] = num;
            }
        }
    }

    ll ans = 0;
    for (ll summ = 0; summ <= N*(K-1); summ++) {
        ans = (ans + ways[summ] - ways2[summ%K][summ] + MOD) % MOD;
    }

    cout << ans;
}