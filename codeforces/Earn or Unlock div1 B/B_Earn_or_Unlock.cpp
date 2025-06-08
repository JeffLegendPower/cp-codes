// https://codeforces.com/contest/1854/problem/B

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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

    int a[N];
    ll pres[N + 1];
    pres[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        pres[i + 1] = pres[i] + a[i];
    }

    bitset<200000> dp;
    bitset<200000> dppre;

    dp[0] = 1;
    // cout << dp << endl;
    // for (int i = 1; i < N; i++) dp[i] = -1;

    // dp = dp | ((dp ^ dppre) << a[0]);
    //     dppre[0] = dp[0];
    for (int i = 0; i < N; i++) {
        dp = dp | ((dp ^ dppre) << a[i]);
        dppre[i] = dp[i];
    }

    ll most = 0;

    for (ll i = 0; i < 2 * N; i++) {
        if (dp[i]) {

            most = max(most, pres[min(i + 1, N)] - i);
        }
    }

    cout << most << endl;
}