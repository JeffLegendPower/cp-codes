// https://codeforces.com/problemset/problem/1884/D

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> cnt(N + 1, 0);
        vector<bool> good(N + 1, true);

        set<int> used;
        for (int i = 0; i < N; i++) {
            int a; cin >> a;
            cnt[a]++;

            if (used.find(a) == used.end()) for (int j = a; j <= N; j += a) good[j] = false;
            used.insert(a);
        }

        // num pairs that give gcd=i
        vector<ll> dp(N + 1, 0);

        ll ways = 0;
        for (int g = N; g >= 1; g--) {
            ll total = 0;
            for (int i = g; i <= N; i += g) {
                total += cnt[i];
                dp[g] -= dp[i];
            }

            dp[g] += total * (total - 1) / 2;

            ways += good[g] * dp[g];
        }

        cout << ways << endl;
    }
}