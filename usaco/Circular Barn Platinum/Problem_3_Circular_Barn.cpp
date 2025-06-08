// https://usaco.org/index.php?page=viewproblem2&cpid=626

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


#define ld long double

struct line {
    ll a, b;

    ll calc(ll x) { return a*x + b; }
    ld intersect(line two) { return (ld) (two.b - b) / (a - two.a); };
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("cbarn");

    int N, K;
    cin >> N >> K;

    ll a[N]; for (int i = 0; i < N; i++) cin >> a[i];

    ll best = 1e18;

    // dp[i][j][k] is min cost for satisfying range starting from i and of length (j+1) using (k+1) doors
    ll dp[N][N][K];
    for (int i = 0; i < N; i++) {
        dp[i][0][0] = 0;
        for (int j = 1; j < N; j++) {
            dp[i][j][0] = dp[i][j-1][0] + j*a[(i+j)%N];

            if (j == N-1) best = min(best, dp[i][j][0]);
        }
    }

    for (int k = 1; k < K; k++) {
        for (int l = 0; l < N; l++) {
            ll pre[N+1], summ[N+1];
            pre[0] = 0, summ[0] = 0;
            for (int i = 0; i < N; i++) {
                pre[i+1] = pre[i] + a[(l+i)%N];
                summ[i+1] = summ[i] + i*a[(l+i)%N];
            }

            deque<line> hull;
            hull.push_back({
                -1,
                dp[l][1-1][k-1] - summ[1] + 1*pre[1]
            });

            for (int len = 2; len <= N; len++) {
                ll x = pre[len];
                while (hull.size() >= 2 && hull[0].calc(x) >= hull[1].calc(x)) hull.pop_front();

                dp[l][len-1][k] = summ[len] + hull[0].calc(x);

                line cur = {
                    -len,
                    dp[l][len-1][k-1] - summ[len] + len*pre[len]
                };

                while (hull.size() >= 2 && hull[hull.size() - 2].intersect(hull.back()) > hull[hull.size() - 2].intersect(cur)) hull.pop_back();
                hull.push_back(cur);

                if (len == N) best = min(best, dp[l][len-1][k]);
            }
        }
    }
    
    cout << best;
}