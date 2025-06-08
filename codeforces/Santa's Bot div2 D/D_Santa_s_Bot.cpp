// https://codeforces.com/contest/1279/problem/D

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

ll MOD = 998244353;

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll modinv(ll x) {
    return binpow(x, MOD - 2);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    // cout << MOD << endl;

    vector<ll> chancepick(1e7 + 1, 0);
    vector<ll> chancewant(1e7 + 1, 0);

    for (int i = 0; i < N; i++) {
        int k;
        cin >> k;

        set<int> used;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            chancepick[a] = (chancepick[a] + modinv(N * k)) % MOD;

            if (used.find(a) == used.end()) {
                used.insert(a);
                
                chancewant[a] = (chancewant[a] + modinv(N)) % MOD;
            }
        }
    }

    ll chance = 0;
    for (int i = 0; i <= 1e7; i++) {
        chance = (chance + (chancepick[i] * chancewant[i]) % MOD) % MOD;
    }

    cout << chance;
}