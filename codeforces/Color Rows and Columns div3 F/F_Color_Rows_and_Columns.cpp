// https://codeforces.com/contest/2000/problem/F

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
        int N, k;
        cin >> N >> k;
        k += 20;

        vector<ll> dp(k + 1, 1e18);
        vector<ll> dp2(k + 1, 1e18);
        dp[0] = 0;


        for (int i = 0; i < N; i++) {
            int a, b;
            cin >> a >> b;
            ll cost = min(a, b);
            ll num = max(a, b) - 1;

            if (i % 2 == 0) {
                for (int j = 0; j <= k; j++) dp2[j] = dp[j];
            } else {
                for (int j = 0; j <= k; j++) dp[j] = dp2[j];
            }

            ll total = 0;
            ll saved = 0;
            while (a > 0 && b > 0) {
                if (a >= b) {
                    total += b;
                    a--;
                    saved++;
                    if (a == 0) saved++;
                } else {
                    total += a;
                    b--;
                    saved++;
                    if (b == 0) saved++;
                }

                for (int l = k - saved; l >= 0; l--) {
                    if (i % 2 == 0) dp2[l + saved] = min(dp2[l + saved], dp[l] + total);
                    else dp[l + saved] = min(dp[l + saved], dp2[l] + total);
                }
            }
        }

        k -= 20;

        ll ans = 1e18;
        for (int i = k; i <= k + 20; i++) {
            if (N % 2 == 1) ans = min(ans, dp2[i]);
            else ans = min(ans, dp[i]);
        }

        if (ans == 1e18) cout << -1 << endl;
        else cout << ans << endl;
    }
}