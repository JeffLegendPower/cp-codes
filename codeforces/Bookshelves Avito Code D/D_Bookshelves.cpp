// https://codeforces.com/contest/981/problem/D

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

    int N, k;
    cin >> N >> k;

    ll a[N];
    ll andpre[N + 1][50];
    for (int i = 0; i < 50; i++) andpre[0][i] = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        for (int j = 0; j < 50; j++) {
            andpre[i + 1][j] = andpre[i][j];
            if (a[i] & (1ll<<j)) andpre[i + 1][j]++;
        }
    }

    ll mask = 0;

    for (int bit = 60; bit >= 0; bit--) {
        ll target = mask | (1ll<<bit);

        // Whether a supermask of target is possible for all elements up to i with k segments
        bool dp[N][k];
        for (int i = 0; i < N; i++) for (int j = 0; j < k; j++) dp[i][j] = false;

        ll summ = 0;
        for (int i = 0; i < N; i++) {
            summ += a[i];
            if ((summ & target) == target)
                dp[i][0] = true;
        }

        for (int ki = 1; ki < k; ki++) {
            for (int i = ki; i < N; i++) {
                summ = a[i];
                for (int j = i - 1; j >= 0; j--) {
                    if (((summ & target) == target) && dp[j][ki - 1]) dp[i][ki] = true;
                    summ += a[j];
                }
            }
        }

        if (dp[N - 1][k - 1]) mask = target;
    }

    cout << mask << endl;
}