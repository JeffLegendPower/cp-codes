// https://summer24.teamscode.org/contest/3/problem/C

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


ll compute_hash(string const& s) {
    const int p = 31;
    // const int m = 1e7 + 9;
    const int m = 1e9 + 7;
    ll hash_value = 0;
    ll p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

ll binpow(ll a, ll b, ll MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll modinverse(ll a, ll MOD) {
    return binpow(a, MOD - 2, MOD);
}


int main() {
    freopen("/Users/ishaangoyal/Desktop/USACO:Codeforces/teamscode/Phonier/all_titles.txt", "r", stdin);

    set<ll> hashes;
    
    cout << "{";
    for (int i = 0; i < 4000; i++) {
    // for (int i = 0; i < 10; i++) {
        string s;
        getline(cin, s);
        ll hash = compute_hash(s);
        hashes.insert(hash);
        cout << hash << ",";
        if (i % 100 == 99) cout << endl;
    }
    cout << "};";

    // cout << hashes.size();
}