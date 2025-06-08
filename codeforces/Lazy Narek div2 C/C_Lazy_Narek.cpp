// https://codeforces.com/contest/2005/problem/C

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

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        string ss[N];
        for (int i = 0; i < N; i++) cin >> ss[i];

        // min del if starts with 'n', 'a', 'r', 'e', 'k'
        char cs[5] = {'n', 'a', 'r', 'e', 'k'};
        set<char> css;
        css.insert('n');
        css.insert('a');
        css.insert('r');
        css.insert('e');
        css.insert('k');

        // 
        plli scores[5][N];

        for (int i = 0; i < N; i++) {
            int k = 0;
            for (char c : cs) {
                scores[k][i] = {0, k};
                int charidx = k;
                for (int j = 0; j < M; j++) {
                    if (ss[i][j] == cs[charidx]) {
                        charidx = (charidx + 1) % 5;
                        if (charidx == 0) scores[k][i].first += 5;
                    } else if (css.find(ss[i][j]) != css.end()) scores[k][i].first--;
                }

                scores[k][i].second = charidx;
                // cout << i << " " << k << " " << scores[k][i].first << endl;
                k++;
            }
        }

        ll dp[N + 1][5];
        dp[0][0] = 0;
        dp[0][1] = -1e9;
        dp[0][2] = -1e9;
        dp[0][3] = -1e9;
        dp[0][4] = -1e9;

        for (int i = 0; i < N; i++) {
            dp[i + 1][0] = dp[i][0];
            dp[i + 1][1] = dp[i][1];
            dp[i + 1][2] = dp[i][2];
            dp[i + 1][3] = dp[i][3];
            dp[i + 1][4] = dp[i][4];

            for (int j = 0; j < 5; j++) {
                if (dp[i][j] == -1e9) continue;
                dp[i + 1][scores[j][i].second] = max(dp[i + 1][scores[j][i].second], dp[i][j] + scores[j][i].first);
            }
        }

        ll best = 0;
        for (int i = 0; i < 5; i++) best = max(best, dp[N][i] - i);
        cout << best << endl;
    }
}