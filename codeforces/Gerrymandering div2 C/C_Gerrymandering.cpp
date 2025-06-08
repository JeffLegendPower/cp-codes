// https://codeforces.com/contest/2022/problem/C

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

const int MAXN = 1e6;
ll x[2][MAXN];
ll dp[MAXN][3];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        for (int i = 0; i < N; i++) {
            x[0][i] = 1;
            x[1][i] = 1;
        }

        for (int i = 0; i < N; i++) {
            char c; cin >> c;
            if (c == 'J') x[0][i] = 0;
        } for (int i = 0; i < N; i++) {
            char c; cin >> c;
            if (c == 'J') x[1][i] = 0;
        }

        for (int i = 0; i <= N; i++) for (int j = 0; j < 3; j++) dp[i][j] = -1e9;
        dp[0][1] = 0;

        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < 3; j++) {
                int finish = j - 1 + i;
                
                if ((i + finish) % 3 != 0) continue;
                if (finish > N) break;

                if (i >= 3 && finish >= 3) dp[i][j] = max(dp[i][j], dp[i - 3][j] + ((x[0][i - 1] + x[0][i - 2] + x[0][i - 3]) >= 2) + ((x[1][finish - 1] + x[1][finish - 2] + x[1][finish - 3]) >= 2));
                if (j == 0) dp[i][j] = max(dp[i][j], dp[i - 2][1] + ((x[0][i - 1] + x[0][i - 2] + x[1][i - 2]) >= 2));
                else if (j == 1) {
                    dp[i][j] = max(dp[i][j], dp[i - 2][2] + ((x[0][i - 1] + x[0][i - 2] + x[1][i - 1]) >= 2));
                    dp[i][j] = max(dp[i][j], dp[i - 1][0] + ((x[0][i - 1] + x[1][i - 1] + x[1][i - 2]) >= 2));
                } else dp[i][j] = max(dp[i][j], dp[i - 1][1] + ((x[0][i - 1] + x[1][i] + x[1][i - 1]) >= 2));
            }
        }

        cout << dp[N][1] << endl;
    }
}