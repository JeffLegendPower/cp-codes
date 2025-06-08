// https://cses.fi/problemset/task/1082

// First we can solve this in O(n) by iterating through each possible divisor
// From 1 to n (since the maximum divisor is n)
// We can get the number of times this number k is a divisor from 1..n by doing floor(n/k)
// However, that is too slow
// We can do this in O(sqrt(n)) by noticing that there are strips of the same frequency that become longer in length
// So we can calculate entire strips together to make it O(sqrt(n))
// To get the length of each strip we will be starting at the first index of the strip, so we need to find the last
// index of the strip, which can be done by finding floor(n/freq)
// Now we can use the arithmetic sum to get the sum of divisors of a strip
// However since the arithmetic sum has division by 2, we need to instead multiply it by
// the modular inverse of 2 (mod 1e9 + 7)

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
    ll n;
    cin >> n;

    ll MOD = 1e9 + 7;

    ll divisorSum = 0;

    for (ll i = 1; i <= n; i++) {
        ll div = n / i;
        ll end = n / div;
        ll count = end - i + 1;

        ll next = end;

        div %= MOD;
        count %= MOD;

        ll summ = (i + end);
        summ %= MOD;
        summ *= count;
        summ %= MOD;
        summ *= 500000004;
        summ %= MOD;

        divisorSum += (div * summ) % MOD;
        divisorSum %= MOD;
        i = next;
    }

    cout << divisorSum;
}