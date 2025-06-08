// https://codeforces.com/contest/1700/problem/D

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
    int N;
    cin >> N;

    ll v[N];
    ll pre[N + 1];
    pre[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        pre[i + 1] = pre[i] + v[i];
    }

    // Time it takes to fill the first i locks with the first i pipes
    // dp[i] = max(dp[i - 1], ceil(pre[i + 1] / i))
    // For the time it takes to fill the ith lock, if we can fill every lock at or before that moment
    // It will take ceil(pre[i + 1] / i) time
    // Otherwise, it will take dp[i - 1] time because even though the ith lock is filled, all the other locks before
    // that are not done filling up, so we still have to wait for that
    ll dp[N];
    dp[0] = v[0];
    // Time it takes to fill all the locks with the first i pipes
    // time[i] = max(dp[i], ceil(pre[N] / i))
    // This is because if we are able to fill all the locks before some pipes have filled
    // the entire thing, then it will take ceil(pre[N] / i) time
    // Otherwise some pipes who finished filling their locks might fill the entire thing
    // before others could fill their locks, so in that case it would take dp[i] time
    ll time[N];
    time[0] = ceil(pre[N]);

    // Time to fill all the locks with the first i pipes
    for (int i = 1; i < N; i++) {
        dp[i] = ceil(pre[i + 1] / (double) (i + 1));
        dp[i] = max(dp[i], dp[i - 1]);
        time[i] = ceil(pre[N] / (double) (i + 1));
        time[i] = max(time[i], dp[i]);
    }

    // Now for each query we can just use binary search to find how many locks are needed to
    // satisfy the time constraint
    int Q;
    cin >> Q;
    while (Q--) {
        ll t;
        cin >> t;

        // Case when its impossible to fill within the time constraint
        if (time[N - 1] > t) {
            cout << -1 << endl;
            continue;
        }

        int low = 0, high = N - 1;
        int best = N - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (time[mid] > t) low = mid + 1;
            else {
                high = mid - 1;
                best = min(best, mid);
            }
        }

        cout << best + 1 << endl;
    }
}