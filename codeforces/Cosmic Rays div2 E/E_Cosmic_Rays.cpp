// https://mirror.codeforces.com/contest/2002/problem/E

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
const int Nmax = 1e6;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(res, t[--r]);
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

    int T2 = T;

    while (T--) {
        cin >> N;
        for (int i = 0; i < 2*N; i++) t[i] = 0;
        build();

        plli nums[N];

        for (int i = 0; i < N; i++) cin >> nums[i].first >> nums[i].second;

        // i=5 is bad

        // if (T2 == 10000) {
        //     if (T == T2 - 5) {
        //         cout << N << endl;
        //         for (int i = 0; i < N; i++) cout << nums[i].first << " " << nums[i].second << endl;
        //     }
        //     continue;
        // }

        // value, how far back it goes
        plli dp[N];
        ll greatest[N + 1];
        greatest[0] = 0;
        vector<vector<int>> lastidx(N + 1);

        for (int i = 0; i < N; i++) {
            int val = nums[i].second;
            ll cnt = nums[i].first;
            dp[i] = cnt;
            if (lastidx[val].empty()) {
                modify(i, dp[i]);
                greatest[i + 1] = max(greatest[i], dp[i]);
                lastidx[val].push_back(i);

                // cout << greatest[i + 1] << " ";
                continue;
            }

            int last = lastidx[val];
            ll lastdp = dp[last];
            ll between = query(last + 1, i);

            if (cnt > between && lastdp > between) 
            dp[i] = max(dp[i], cnt + lastdp - between);

            modify(i, dp[i]);
            greatest[i + 1] = max(greatest[i], dp[i]);
            lastidx[val] = i;

            // cout << greatest[i + 1] << " ";
        }
        cout << endl;

        for (int i = 0; i < N; i++) cout << dp[i] << endl;
    }
}