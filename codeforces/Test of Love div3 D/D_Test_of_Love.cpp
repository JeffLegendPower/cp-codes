// https://codeforces.com/contest/1992/problem/D

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

    while (T--) {
        int N, m, k;
        cin >> N >> m >> k;

        string s = "S";
        string s2;
        cin >> s2;
        s += s2;
        s += "SS";

        // number will be how many times we swam (minimize it);
        // First one is the bank, last 2 are the shore (bc of crocodiles)
        int dp[N + 3];
        for (int i = 0; i < N + 3; i++) dp[i] = 1e6;
        // Starting on the bank
        dp[0] = 0;
        for (int i = 0; i < N + 3; i++) {
            // Jumping
            if (s[i] == 'S' || s[i] == 'L') {
                for (int j = 1; j <= m; j++) {
                    if (i + j >= N + 3) break;
                    // Crocodile in the way
                    if (s[i + j] == 'C') continue;
                    // if (s[i + j - 1] == 'C' || (i + j + 1 < N + 3 && s[i + j + 1] == 'C')) continue;
                    int next = dp[i];
                    if (s[i + j] == 'W') next++;
                    dp[i + j] = min(dp[i + j], next);
                }
            }

            // Swimming
            if (s[i] == 'W') {
                if (i + 1 >= N + 3) continue;
                if (dp[i + 1] == 'C') continue;
                
                int next = dp[i];
                if (s[i + 1] == 'W') next++;
                // if (i + 2 < N + 3 && dp[i + 2] == 'C') continue;
                dp[i + 1] = min(dp[i + 1], next);
            }
        }

        // for (int i = 0; i < N + 3; i++) cout << dp[i] << " ";

        int swim = min(dp[N + 1], dp[N + 2]);
        if (swim <= k) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}