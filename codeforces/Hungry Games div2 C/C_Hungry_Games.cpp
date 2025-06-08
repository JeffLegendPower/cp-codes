// https://codeforces.com/contest/1994/problem/C

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


void solve() {
    ll n, x;
    cin >> n >> x;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll count = 0;
    ll l = 0;
    ll curr = 0;
    vector<ll> zeroes(n, 0);
    for (int i = 0; i < n; i++) {
        curr += a[i];
        while (curr > x) {
            ll temp = l == 0 ? 0 : zeroes[l - 1];

            // cout << l << " " << i << " " << curr << " " << temp << endl;
            count += 1 + temp;
            zeroes[i] += 1 + temp;

            curr -= a[l];
            l++;
        }
    }

    while (curr > x) {
        count++;
        curr -= a[l];
        l++;
    }


    // cout << count << endl;
    cout << n * (n + 1) / 2 - count << endl;
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        solve();
    }
}