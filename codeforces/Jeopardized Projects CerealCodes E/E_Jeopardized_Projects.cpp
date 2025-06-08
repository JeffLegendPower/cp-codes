// https://codeforces.com/gym/103886/problem/E

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
    bool operator() (const plli& a, const plli& b) const {
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

// num half-palindromes with sum i
ll ways[100001];
ll pre[100001];
ll MOD = 1e9 + 7;

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ways[0] = 1;
    ways[1] = 1;
    pre[0] = 1;
    pre[1] = 2;
    for (int i = 2; i <= 100000; i++) {
        ways[i] = (ways[i - 1] * 2) % MOD;
        pre[i] = (pre[i - 1] + ways[i]) % MOD;
    }

    ll palindromes[100001];
    palindromes[0] = 0;
    for (int i = 1; i <= 100000; i++) {
        palindromes[i] = (palindromes[i - 1] + pre[(i-1) / 2]) % MOD;
        if (i % 2 == 0) palindromes[i] = (palindromes[i] + ways[i / 2]) % MOD;
    }

    int T;
    cin >> T;

    while (T--) {
        int l, r;
        cin >> l >> r;
        ll ans = (pre[r] - pre[l - 1] + MOD) % MOD;
        ans = (ans - palindromes[r] + palindromes[l - 1] + MOD) % MOD;
        cout << ans << endl;
    }
}