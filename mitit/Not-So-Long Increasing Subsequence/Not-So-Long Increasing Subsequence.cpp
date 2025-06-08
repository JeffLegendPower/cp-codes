// https://mitit.org/Contest/ViewProblem/lis-p?cid=advanced1-2025

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

struct comp {
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;

        ll a[N];
        for (int i = 0; i < N; i++) cin >> a[i];

        // dp[i][j] = {a, b}: seq of length j ending at i with minimum increasing subseq of length b and prev element a
        pii dp[N][K];
        for (int i = 0; i < N; i++) for (int j = 0; j < K; j++) dp[i][j] = {-1, -1}

        pii dpprev[N+1][K]  ;
        int sol = -1;
        for (int i = 0; i < (K+1)/2; i++) dpprev[0][i] = {1e6, -1};
        for (int i = 0; i < N; i++) {
            dp[i][0][0] = -1;

            for (int j = 1; j < K; j++) {
                for (int k = )
            }
            for (int j = 1; j < (K+1)/2; j++) {
                if (dpprev[i][j-1].first < a[i]) {
                    dp[i][j] = dpprev[i][j-1].second;
                }
            }

            if (dp[i][(K+1)/2 - 1]) {
                sol = i;
                break;
            }

            for (int j = 0; j < (K+1)/2; j++) {
                dpprev[i+1][j] = dpprev[i][j];
                if (dp[i][j] > -2 && a[i] < dpprev[i+1][j].first) {
                    dpprev[i+1][j] = {a[i], i};
                }
            }
        }

        if (sol == -1) {
            cout << "NO" << endl;
            continue;
        }

        vector<int> idxs;
        int k = (K+1)/2 - 1;
        while (sol != -1) {
            idxs.push_back(sol);
            sol = dp[sol][k--];
        }

        reverse(idxs.begin(), idxs.end());
        cout << "YES" << endl;
        for (int idx : idxs) cout << idx << " ";
        cout << endl;
    }
}