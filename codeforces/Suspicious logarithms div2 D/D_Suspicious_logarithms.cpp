// https://codeforces.com/contest/1891/problem/D

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
    int T;
    cin >> T;

    ll MOD = 1e9 + 7;

    ll lowval[63];
    ll highstart[63];

    lowval[0] = 0;
    lowval[1] = 0;
    for (int i = 2; i < 60; i++) {
        ll num1 = 1ll << i;
        lowval[i] = floor(log(num1) / log(i));

        ll num2 = (1ll << (i + 1)) - 1;
        ll highval = floor(log(num2) / log(i));

        if (highval == lowval[i]) highstart[i] = -1;
        else {
            highstart[i] = num2;
            ll low = num1 + 1, high = num2;
            while (low <= high) {
                ll mid = low + (high - low) / 2;
                if (floor(log(mid) / log(i)) == highval) {
                    high = mid - 1;
                    highstart[i] = min(highstart[i], mid);
                } else low = mid + 1;
            }
        }

        // cout << i << " " << lowval[i] << " " << highstart[i] << endl;
    }
    // cout << LLONG_MAX << endl;

    while (T--) {
        ll l, r;
        cin >> l >> r;

        ll sum = 0;

        for (int i = 2; i < 60; i++) {
            ll low = max(1ll << i, l);
            ll high = min((1ll << (i + 1)) - 1, r);
            if (low > high) continue;
            cout << low << " " << high << " " << highstart[i] << endl;

            // cout << sum << endl;
            ll oldsum = sum;

            if (highstart[i] == -1) {
                sum += lowval[i] * ((high - low + 1));
                // cout << low << " " << high << " " << highstart[i] << endl;
                // cout << (high - low + 1) << " " << lowval[i] << endl;
                // sum %= MOD;
                continue;
            }

            ll numlow, numhigh;
            if (low >= highstart[i]) {
                numlow = 0;
                numhigh = high - low + 1;
            } else if (high < highstart[i]) {
                numlow = high - low + 1;
                numhigh = 0;
            } else {
                numlow = highstart[i] - low;
                numhigh = high - highstart[i] + 1;
            }
            sum += (numlow) * lowval[i];
            // sum %= MOD;
            sum += (numhigh) * (lowval[i] + 1);
            // sum %= MOD;
            // cout << low << " " << high << " " << highstart[i] << " " << lowval[i] << endl;
            // cout << sum - oldsum << endl;
            // cout << numhigh << " e " << lowval[i] + 1 << endl;
        }
        cout << sum << endl;
    }
}