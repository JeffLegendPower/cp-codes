// https://codeforces.com/contest/1993/problem/D

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

        int endsize = N % k;
        if (endsize == 0) endsize = k;

        ll a[N];
        ll A = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            A = max(A, a[i]);
        }

        // ll low = 0, high = A;
        ll low = 8, high = 8;
        int best = 0;
        while (low <= high) {
            ll mid = low + (high - low) / 2;

            int numless = 0;
            int targetless = (endsize + 1) / 2 - 1;

            for (int i = 0; i < N; i++) numless += a[i] < mid;
            int targetremove = numless - targetless;

            // how many < mid can we remove
            int dp[N];
            int less = 0;
            for (int i = 0; i < k; i++) {
                dp[i] = 0;
                if (a[i] < mid) less++;
            } for (int i = k - 1; i < N; i++) {
                dp[i] = less;
                if (i > 0) dp[i] = max(dp[i], dp[i - 1]);
                if (i >= k) dp[i] = max(dp[i], less + dp[i - k]);

                cout << i << " " << dp[i] << " " << less << endl;
                
                less -= a[i - k + 1] < mid;
                if (i < N - 1) less += a[i + 1] < mid;
            }

            if (dp[N - 1] >= targetremove) {
                low = mid + 1;
                best = mid;
            } else high = mid - 1;
        }

        cout << best << endl;
    }
}