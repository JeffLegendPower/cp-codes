// https://atcoder.jp/contests/abc321/tasks/abc321_f

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

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

    int Q, K;
    cin >> Q >> K;

    ll MOD = 998244353;
    
    vector<ll> dp(K + 1, 0);
    dp[0] = 1;

    while (Q--) {
        char op;
        int x;
        cin >> op >> x;
        if (x > K) {
            cout << dp[K] << endl;
            continue;
        }

        if (op == '+') {
            for (int i = K - x; i >= 0; i--) {
                dp[i + x] = (dp[i + x] + dp[i]) % MOD;
            }
        } else if (op == '-') {
            for (int i = 0; i <= K - x; i++) {
                dp[i + x] = (MOD + dp[i + x] -  dp[i]) % MOD;
            }
        }

        cout << dp[K] << endl;
    }
}