// https://codeforces.com/contest/1928/problem/D

// This problem can be solved using ternary search
// A naive approach would be to test every value of k
// The bounds for k would be 1 <= k <= max(c)
// However, testing each k would take O(n) time, making the algorithm too slow
// However, as k increases, the penalty for a bigger group increases (or decreases strength) at a linear rate
// and as k increases, the strength gained from a more spread out race increases at a decreasing rate
// So, the sum of these functions would have at most 1 extrema, allowing us to use ternary search on k
// to find the max. This results in our algorithm taking O(n * log(k)) time

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

ll k_strength(ll k, vector<ll> &c, int N, ll x, ll b) {
    ll strength1 = -(k - 1) * x;
    for (int i = 0; i < N; i++) {
        if (c[i] < k) {
            strength1 += b * (c[i] - 1) * (c[i]) / 2;
            continue;
        }

        ll cur = c[i];
        ll numfloor = k;
        ll divnfloor = c[i] / k;
        ll numceil = c[i] - divnfloor * k;
        ll divnceil = divnfloor + (c[i] % k == 0 ? 0 : 1);
        numfloor -= numceil;

        ll add = divnfloor * divnfloor * (numfloor - 1) * (numfloor) / 2;
        add += divnceil * divnceil * (numceil - 1) * (numceil) / 2;
        add += divnfloor * divnceil * numfloor * numceil;

        strength1 += add * b;
    }
    return strength1;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        ll b, x;
        cin >> N >> b >> x;

        vector<ll> c;
        ll low = 1, high = 1;
        for (int i = 0; i < N; i++) {
            ll ci;
            cin >> ci;
            c.push_back(ci);
            high = max(high, c[i]);
        }

        while (high - low > 1) {
            ll mid1 = low + (high - low) / 3;
            ll mid2 = high - (high - low) / 3;

            ll strength1 = k_strength(mid1, c, N, x, b);
            ll strength2 = k_strength(mid2, c, N, x, b);

            if (strength1 < strength2) low = mid1 + 1;
            else high = mid2 - 1;
        }

        cout << max(k_strength(low, c, N, x, b), k_strength(high, c, N, x, b)) << endl;
    }
}