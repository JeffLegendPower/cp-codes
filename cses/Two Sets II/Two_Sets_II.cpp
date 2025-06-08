// https://cses.fi/problemset/task/1093

// This problem had me stumped
// How ironic that the most classic knapsack problem came the hardest to me

// Since n <= 500 and the sum of 1..500 is 125250, we can solve this problem using
// knapsack dp in O(n * sum(1..n))
// We will only want to count the number of ways that one set could make a sum of sum(1..n) / 2
// Which can easily be done by counting the number of ways to achieve any sum from 1..sum(1..n)
// in a dp array, then iterating i from 1 to n and adding dp[x - i] to dp[x]
// However, we need to create 2 sets, and we can overcount by accidentally counting a second set in a pair
// where we already counted. the first set
// ex. n=7 and we count {1, 3, 4, 6} but then also count {2, 5, 7} but they are both part of the same pair
// So let's just assume that one set always has to contain 1, which will prevent any overcounting as
// we can't overcount any second sets as none of them will contain 1

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
    ll N;
    cin >> N;

    ll MOD = 1e9 + 7;

    ll sum = N * (N + 1) / 2;
    if (sum % 2 == 1) {
        cout << 0;
        return 0;
    }

    ll dp[sum + 1];
    dp[1] = 1;
    dp[0] = 1;
    for (ll i = 2; i <= sum; i++) dp[i] = 0;

    for (ll i = 2; i <= N; i++) {
        for (ll target = sum; target >= i + 1; target--) {
            dp[target] += dp[target - i];
            dp[target] %= MOD;
        }
    }

    cout << dp[sum / 2];
}