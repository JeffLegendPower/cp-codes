// https://usaco.org/index.php?page=viewproblem2&cpid=1307&lang=en

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}


int diff(int x, int y) {
    if (x < y) return 0;
    else if (x == y) return 1;
    else return 2;
}

ll MOD = 1e9 + 7;
// x is which digit we are building off of 
ll solveQ(vector<int> &a, int l, int r, string A, string B) {
    // left digit
    // right digit
    // <, =, or > A
    // <, =, or > B
    ll dp[19][19][3][3];

    for (int i = 0; i < 19; i++) for (int j = 0; j < 19; j++) for (int k = 0; k < 3; k++) for (int m = 0; m < 3; m++) dp[i][j][k][m] = 0;

    for (int i = l; i <= r; i++) {
        for (int len = 19; len >= 1; len--) {
            for (int d1 = 0; d1 < 19; d1++) {
                int d2 = d1 + len - 1;
                if (d2 >= 19) continue;

                // appending to back of number
                if (d2 < 18) {
                    int moreA = diff(a[i], A[d2 + 1] - '0');
                    int lessB = diff(a[i], B[d2 + 1] - '0');

                    dp[d1][d2 + 1][2][0] += dp[d1][d2][2][0];
                    if (moreA >= 1) dp[d1][d2 + 1][moreA][0] += dp[d1][d2][1][0];
                    if (lessB <= 1) dp[d1][d2 + 1][2][lessB] += dp[d1][d2][2][1];
                    if (moreA >= 1 && lessB <= 1) dp[d1][d2 + 1][moreA][lessB] += dp[d1][d2][1][1];

                    dp[d1][d2 + 1][0][0] += dp[d1][d2][0][0];
                    dp[d1][d2 + 1][2][2] += dp[d1][d2][2][2];
                }

                // appending to front of number
                if (d1 > 0) {
                    int moreA = diff(a[i], A[d1 - 1] - '0');
                    int moreB = diff(a[i], B[d1 - 1] - '0');

                    if (moreA != 1 && moreB != 1) {
                        for (int n = 0; n < 3; n++) for (int m = 0; m < 3; m++) dp[d1 - 1][d2][moreA][moreB] += dp[d1][d2][n][m];
                    } else if (moreA == 1 && moreB != 1) {
                        dp[d1 - 1][d2][0][moreB] += dp[d1][d2][0][0] + dp[d1][d2][0][1] + dp[d1][d2][0][2];
                        dp[d1 - 1][d2][1][moreB] += dp[d1][d2][1][0] + dp[d1][d2][1][1] + dp[d1][d2][1][2];
                        dp[d1 - 1][d2][2][moreB] += dp[d1][d2][2][0] + dp[d1][d2][2][1] + dp[d1][d2][2][2];
                    } else if (moreA != 1 && moreB == 1) {
                        dp[d1 - 1][d2][moreA][0] += dp[d1][d2][0][0] + dp[d1][d2][1][0] + dp[d1][d2][2][0];
                        dp[d1 - 1][d2][moreA][1] += dp[d1][d2][0][1] + dp[d1][d2][1][1] + dp[d1][d2][2][1];
                        dp[d1 - 1][d2][moreA][2] += dp[d1][d2][0][2] + dp[d1][d2][1][2] + dp[d1][d2][2][2];
                    } else {
                        for (int n = 0; n < 3; n++) {
                            for (int m = 0; m < 3; m++) {
                                dp[d1 - 1][d2][n][m] += dp[d1][d2][n][m];
                            }
                        }
                    }
                }
            }
        }

        for (int d = 0; d < 19; d++) {
            int moreA = diff(a[i], A[d] - '0');
            int moreB = diff(a[i], B[d] - '0');
            dp[d][d][moreA][moreB]++;
        }
    }

    ll total = 0;
    for (int d = 0; d < 19; d++) {
        total += dp[d][18][1][0] + dp[d][18][1][1] + dp[d][18][2][0] + dp[d][18][2][1];

        if (A[d] - '0' > 0) break;
    }

    return total;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    string A, B;
    cin >> N >> A >> B;

    while (A.size() < 19) A = '0' + A;
    while (B.size() < 19) B = '0' + B;

    vector<int> a(N); for (int i = 0; i < N; i++) cin >> a[i];

    int Q; cin >> Q;

    while (Q--) {
        int l, r; cin >> l >> r;
        l--, r--;
        cout << solveQ(a, l, r, A, B) << endl;
    }
}