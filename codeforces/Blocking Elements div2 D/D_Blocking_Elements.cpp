// https://codeforces.com/contest/1918/problem/D

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
        int N;
        cin >> N;

        ll pres[N + 1];
        ll a[N];
        pres[0] = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            pres[i + 1] = pres[i] + a[i];
        }

        ll low = 1, high = 1e14;
        ll best = 1e14;

        while (low <= high) {
            ll target = low + (high - low) / 2;


            ll dp[N];
            dp[0] = a[0];
            map<ll, int> minwindow;
            minwindow[0]++;
            minwindow[dp[0]]++;
            int l = 0;
            ll summ = a[0];

            for (int i = 1; i < N; i++) {
                while (summ > target) {
                    summ -= a[l];
                    ll num = 0;
                    if (l > 0) num = dp[l - 1];
                    minwindow[num]--;
                    if (minwindow[num] == 0) minwindow.erase(num);
                    l++;
                }
                // cout << i << " " << l << endl;

                dp[i] = 1e18;

                dp[i] = a[i] + minwindow.begin()->first;

                // for (int j = i - 1; j >= 0; j--) {
                //     if (summ > target) break;
                //     dp[i] = min(dp[i], a[i] + dp[j]);
                //     summ += a[j];
                // }
                // if (summ <= target) dp[i] = min(dp[i], a[i]);

                // cout << dp[i] << endl;
                summ += a[i];
                minwindow[dp[i]]++;

                // cout << dp[i] << " ";
            }


            // for (int i = 0; i < N; i++) cout << dp[i] << " ";
            // cout << endl;

            // ll summ = 0;
            // ll curblock = 0;
            // for (int i = 0; i < N; i++) {
            //     if (curblock + a[i] > target) {
            //         curblock = 0;
            //         summ += a[i];
            //     } else curblock += a[i];

            //     cout << summ << " " << curblock << endl;
            // }

            bool possible = false;
            summ = 0;
            for (int i = N - 1; i >= 0; i--) {
                // cout << summ << endl;
                if (summ > target) break;
                if (dp[i] <= target) {
                    possible = true;
                    break;
                }
                summ += a[i];
            }

            if (possible) {
                best = target;
                high = target - 1;
            } else low = target + 1;
        }

        cout << best << endl;
    }
}