// https://codeforces.com/contest/1475/problem/E

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

ll modInverse(ll A, ll M) {
    ll m0 = M;
    ll y = 0, x = 1;

    if (M == 1)
        return 0;

    while (A > 1) {
        ll q = A / M;
        ll t = M;

        M = A % M, A = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}


vector<ll> factorial;

ll ncr(ll r, ll n, ll MOD) {
    ll res = factorial[n];
    ll bottom = (factorial[n - r] * factorial[r]) % MOD;
    res = (res * modInverse(bottom, MOD)) % MOD;

    return res;
}

int main() {
    int T;
    cin >> T;

    ll MOD = 1e9 + 7;
    factorial.push_back(1);
    for (ll i = 1; i <= 1000; i++) {
        factorial.push_back((factorial.back() * i) % MOD);
    }

    while (T--) {
        ll N, k;
        cin >> N >> k;

        ll fols[N];
        ll freq[N + 1];
        ll freq2[N + 1];
        for (int i = 0; i <= N; i++) {
            freq[i] = 0;
            freq2[i] = 0;
        } for (int i = 0; i < N; i++) {
            cin >> fols[i];
            freq[fols[i]]++;
        }

        sort(fols, fols + N, greater<ll>());

        ll most = 0;
        for (int i = 0; i < k; i++) {
            most += fols[i];
            freq2[fols[i]]++;
        } 
        ll ways = 1;
        for (int i = 1; i <= N; i++) {
            if (freq2[i] == 0) continue;
            ways *= ncr(freq2[i], freq[i], MOD);
        }

        cout << ways << endl;
    }
}