// https://codeforces.com/contest/1788/problem/D

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    ll x[N];
    set<ll> x1;
    set<ll, greater<ll>> x2;
    map<ll, int> xidx;
    for (int i = 0; i < N; i++) {
        cin >> x[i];
        x1.insert(x[i]);
        x2.insert(x[i]);
        xidx[x[i]] = i;
    }

    ll total = 0;
    ll MOD = 1e9 + 7;

    ll pow2[N + 1];
    pow2[0] = 1;
    for (int i = 1; i <= N; i++) pow2[i] = (pow2[i - 1] * 2) % MOD;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int numeles = N - 2;
            numeles -= j - i - 1;

            ll dist = x[j] - x[i];
            auto beforei = x2.upper_bound(x[i] - dist);
            if (beforei == x2.end()) numeles -= i;
            else numeles -= i - xidx[*beforei] - 1;

            auto afterj = x1.lower_bound(x[j] + dist);
            if (afterj == x1.end()) numeles -= N - j - 1;
            else numeles -= xidx[*afterj] - j - 1;

            total = (total + pow2[numeles]) % MOD;
        }
    }

    cout << total << endl;
}