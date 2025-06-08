// https://codeforces.com/contest/1993/problem/C

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

    int T;
    cin >> T;

    while (T--) {
        ll N, k;
        cin >> N >> k;

        ll a[N];
        vector<ll> mods(2*k, 0);
        ll maxa = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            mods[a[i] % (2*k)]++;
            maxa = max(maxa, a[i]);
        }

        bool works = true;
        for (int i = 0; i < k; i++) {
            if (mods[i] > 0 && mods[i + k] > 0) works = false;
        }

        ll low = 0, high = 2*k - 1;

        for (int i = 0; i < k; i++) {
            if (mods[i] == 0) continue;

            ll lowi = i, highi = i + k - 1;
            low = max(low, lowi);
            high = min(high, highi);
        }

        ll low1 = low, high1 = high, low2 = low, high2 = high;

        for (int i = k; i < 2*k; i++) {
            if (mods[i] == 0) continue;
            // cout << i << endl;

            ll lowi1 = i, highi1 = min(2*k - 1, i + k - 1);
            low1 = max(low1, lowi1);
            high1 = min(high1, highi1);

            if (i > k) {
                ll lowi2 = 0, highi2 = i - k - 1;
                low2 = max(low2, lowi2);
                high2 = min(high2, highi2);
            } else high2 = -1;
        }

        ll mintime = -1;

        for (ll i = maxa + 4*k; i >= maxa; i--) {
            ll i2 = i % (2*k);
            if (low1 <= i2 && i2 <= high1) mintime = i;
            if (low2 <= i2 && i2 <= high2) mintime = i;
        }

        cout << mintime << endl;
    }
}