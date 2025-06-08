// https://codeforces.com/contest/1285/problem/D

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

ll minn = 1e18;
void test(vector<ll> &arr, int bit) {
    ll mask = 1ll<<bit;
    vector<ll> one, two;
    // cout << bit << endl;
    for (ll i : arr) {
        if (i & mask) {
            // cout << mask << " " << i << endl;
            // if (mask == 1) cout << i << " a" << endl;
            one.push_back(i);
        } else {
            // if (mask == 1) cout << i << " b" << endl;
            two.push_back(i);
        }
    }

    if (bit == 0) {
        if (one.size() > 0) for (int i = 0; i < two.size(); i++) two[i] ^= mask;
        if (two.size() == 0) for (int i = 0; i < one.size(); i++) one[i] ^= mask;

        ll most1 = 0, most2 = 0;
        for (int i = 0; i < one.size(); i++) most1 = max(most1, one[i]);
        for (int i = 0; i < two.size(); i++) most2 = max(most2, two[i]);

        if (one.size() > 0) minn = min(minn, most1);
        if (two.size() > 0) minn = min(minn, most2);
        // minn = min(minn, min(most1, most2));

        return;
    }

    if (one.size() == 0) {
        test(two, bit - 1);
    } else if (two.size() == 0) {
        for (int i = 0; i < one.size(); i++) one[i] ^= mask;
        test(one, bit - 1);
    } else {
        for (int i = 0; i < two.size(); i++) two[i] ^= mask;
        test(one, bit - 1);
        test(two, bit - 1);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    test(a, 30);
    cout << minn << endl;

    // ll X = 0;
    // vector<int> bigbits;
    // for (int bit = 30; bit >= 0; bit--) {
    //     ll mask = 1ll<<bit;

    //     int cnt1 = 0, cnt0 = 0;
    //     for (int i = 0; i < N; i++) {
    //         if (a[i] & mask) cnt1++;
    //         else cnt0++;
    //     }

    //     if (cnt0 == 0) X |= mask;
    //     else if (cnt1 != 0) bigbits.push_back(bit);
    // }

    // for (int i = 0; i < N; i++) a[i] ˆ= X;
}