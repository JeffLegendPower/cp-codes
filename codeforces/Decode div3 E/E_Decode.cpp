// https://codeforces.com/contest/1996/problem/E

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
    int T;
    cin >> T;

    ll MOD = 1e9 + 7;

    while (T--) {
        string s;
        cin >> s;
        int N = s.size();

        // -N to 0 to N
        // i = x + N
        ll cnt[2 * N + 1];

        for (int i = 0; i < 2 * N + 1; i++) cnt[i] = 0;

        int val = 0;
        for (int i = 0; i < N; i++) {
            val += (s[i] - '0') * 2 - 1;
            cnt[val + N] += N - i;
            // val += (s[i] - '0') * 2 - 1;
        }

        // cnt[val + N]++;

        // for (int i = 0; i < 2 * N + 1; i++) {
        //     cout << (i - N) << " " << cnt[i] << endl;
        // }

        val = 0;
        ll valid = 0;
        for (ll i = 0; i < N; i++) {
            // cnt[val + N] -= N - i;
            valid += cnt[val + N] * (i + 1);
            valid %= MOD;
            val += (s[i] - '0') * 2 - 1;
            cnt[val + N] -= N - i;
        }

        cout << valid << endl;  
    }
}