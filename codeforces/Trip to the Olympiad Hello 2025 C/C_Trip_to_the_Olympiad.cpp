// https://codeforces.com/contest/2057/problem/C

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        ll l, r;
        cin >> l >> r;

        // cout << (0^7) + (0^8) + (7^8) << endl;
        // 6

        ll a = l, b = r, c = r-1;
        for (int bt = 29; bt >= 0; bt--) {
            // cout << a << " " << b << " " << c << endl;
            ll num = 1ll<<bt;

            ll msk1 = ~((1ll << bt) - 1ll);
            ll msk2 = (1ll << bt) - 1ll;

            int cnt = 0;
            if (a&num) cnt++;
            if (b&num) cnt++;
            if (c&num) cnt++;

            if (cnt == 0) {
                // cout << num << endl;
                // if ((a^num) > r || (a^num) < l) {
                //     ll a2 = (a&msk1)^num;
                //     if (a2 > r || a2 < l) continue;
                //     else a = a2;
                // } else {
                //     a = a^num;
                // }


                ll k = min({a, b, c});

                if ((k^num) > r || (k^num) < l) {
                    ll k2 = min({a&msk1, b&msk1, c&msk1})^num;

                    if (k2 > r || k2 < l) continue;
                    else {
                        if ((a&msk1) <= (b&msk1) && (a&msk1) <= (c&msk1)) {
                            a = k2;
                        } else if ((b&msk1) <= (a&msk1) && (b&msk1) <= (c|msk1)) {
                            b = k2;
                        } else c = k2;
                    }
                } else {
                    if (a <= b && a <= c) a = k^num;
                    else if (b <= a && b <= c) b = k^num;
                    else c = k^num;
                }


            } else if (cnt == 3) {
                ll k = max({a, b, c});

                if ((k^num) > r || (k^num) < l) {
                    ll k2 = max({a|msk2, b|msk2, c|msk2})^num;

                    if (k2 > r || k2 < l) continue;
                    else {
                        if ((a|msk2) >= (b|msk2) && (a|msk2) >= (c|msk2)) {
                            a = k2;
                        } else if ((b|msk2) >= (a|msk2) && (b|msk2) >= (c|msk2)) {
                            b = k2;
                        } else c = k2;
                    }
                } else {
                    if (a >= b && a >= c) a = k^num;
                    else if (b >= a && b >= c) b = k^num;
                    else c = k^num;
                }
            }
        }

        cout << a << " " << b << " " << c << endl;
    }
}