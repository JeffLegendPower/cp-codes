// https://atcoder.jp/contests/dp/tasks/dp_f

// This can be solved with a 2D dp array
// where each axis is the size of string s + 1 or t + 1
// The value at each i, j be the LCS of s[0..i] and t[0..j]
// We can go from dp[i][j] to dp[i + 1][j] or dp[i][j + 1] and will keep the same LCS
// So dp[i + 1][j] := dp[i][j] and dp[i][j + 1] := dp[i][j]
// Or increase the LCS by 1 if s[i] == t[j] so dp[i + 1][j + 1] := dp[i][j] + 1

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


int main() {
    string s, t;
    cin >> s >> t;

    int N = s.size(), M = t.size();

    int dp[N + 1][M + 1];
    dp[0][0] = 0;

    // Have an array to store the direction used so we can effectively reconstruct the LCS
    // by backtracking
    // 0 = from the left, 1 = from above, 2 = from the diagonal (this is where we append to the LCS)
    int last[N + 1][M + 1];

    // Initialize DP array to 0
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) dp[i][j] = 0;
    }

    // Populate the array and update the maximum LCS
    int maxlcs = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

            if (dp[i - 1][j] >= dp[i][j - 1]) last[i][j] = 1;
            else last[i][j] = 0;

            if (s[i - 1] == t[j - 1] && dp[i - 1][j - 1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                last[i][j] = 2;
            }
        }
    }

    // This will be reversed due to backtracking
    vector<char> LCS;
    int i = N, j = M;
    while (i > 0 && j > 0) {
        if (last[i][j] == 0) j--;
        else if (last[i][j] == 1) i--;
        else {
            LCS.push_back(s[i - 1]);
            i--;
            j--;
        }
    }

    for (int k = LCS.size() - 1; k >= 0; k--) {
        cout << LCS[k];
    }
}