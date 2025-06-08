// https://codeforces.com/contest/930/problem/C

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


// Segtree 1
const int Nmax = 2e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int l, int r, int value) {
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}

int query(int p) {
  int res = 0;
  for (p += N; p > 0; p >>= 1) res += t[p];
  return res;
}

void push() {
  for (int i = 1; i < N; ++i) {
    t[i<<1] += t[i];
    t[i<<1|1] += t[i];
    t[i] = 0;
  }
}
// Segtree 1 end

// Segtree 2
int N2;  // array size
int t2[2 * Nmax];

void build2() {  // build the tree
  for (int i = N2 - 1; i > 0; --i) t2[i] = max(t2[i<<1], t2[i<<1|1]);
}

void modify2(int p, int val) {
  for (t2[p += N2] = val; p > 1; p >>= 1) t2[p>>1] = max(t2[p], t2[p^1]);
}

int query2(int l, int r) {
  int res = 0;
  for (l += N2, r += N2; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t2[l++]);
    if (r&1) res = max(res, t2[--r]);
  }
  return res;
}
// Segtree 2 end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    N = m;
    memset(t, 0, sizeof(t));
    build();

    pii ranges[n];
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].first >> ranges[i].second;
        ranges[i].first--;
        ranges[i].second--;

        modify(ranges[i].first, ranges[i].second + 1, 1);
    }

    push();

    // for (int i = 0; i < m; i++) cout << query(i) << " ";
    // cout << endl;

    // max # of elements that are like just non decreasing then goes to non increasing
    // (increasing then decreasing), cant have any bumps or valleys just needs to go up and down

    // int maxes[n + 1];
    // memset(maxes, 0, sizeof(maxes));
    int dp1[m];

    N2 = n + 1;
    memset(t2, 0, sizeof(t2));
    build2();

    for (int i = 0; i < m; i++) {
        int cur = query(i);
        dp1[i] = 1 + query2(0, cur + 1);
        // cout << cur << " " << dp1[i] << endl;

        modify2(cur, dp1[i]);
    }

    memset(t2, 0, sizeof(t2));
    build2();
    int dp2[m];
    for (int i = 0; i < m; i++) {
        int cur = query(i);
        dp2[i] = 1 + query2(cur, n + 2);
        
        modify2(cur, max(dp1[i], dp2[i]));
    }

    cout << max(dp1[m - 1], dp2[m - 1]) << endl;
}