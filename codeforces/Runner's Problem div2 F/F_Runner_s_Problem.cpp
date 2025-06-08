// https://codeforces.com/contest/954/problem/F

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


using Matrix = array<array<ll, 3>, 3>;

ll MOD = 1e9 + 7;

Matrix multi(Matrix one, Matrix two) {
    Matrix ans = {{
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                ans[i][j] += one[i][k] * two[k][j];
                ans[i][j] %= MOD;
            }
        }
    }

    return ans;
}

Matrix binpow(Matrix m, ll b) {
    Matrix res = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};

    while (b > 0) {
        if (b & 1)
            res = multi(res, m);
        m = multi(m, m);
        b >>= 1;
    }
    return res;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    ll M; cin >> N >> M;

    array<ll, 3> obsts[N];
    vector<pll> evnts;
    for (int i = 0; i < N; i++) {
        cin >> obsts[i][0] >> obsts[i][1] >> obsts[i][2];

        evnts.push_back({obsts[i][1], obsts[i][0] - 1});
        evnts.push_back({obsts[i][2], obsts[i][0] - 1});
    }
    evnts.push_back({M, -1});
    sort(evnts.begin(), evnts.end());

    vector<ll> dp[3];
    dp[0].push_back(0);
    dp[1].push_back(1);
    dp[2].push_back(0);
    
    vector<int> blck(3, 0);
    ll last = 1;
    for (int i = 0; i < evnts.size(); i++) {
        if (i > 0 && evnts[i].first == evnts[i - 1].first) {
            if (evnts[i].second >= 0) {
                blck[evnts[i].second] ^= 1;
                if (blck[evnts[i].second]) dp[evnts[i].second].back() = 0;
            }
            continue;
        }

        Matrix m = {{
            {1, 1, 0},
            {1, 1, 1},
            {0, 1, 1}
        }};
        for (int j = 0; j < 3; j++) {
            if (!blck[j]) continue;
            for (int k = 0; k < 3; k++) m[j][k] = 0;
        }
        m = binpow(m, evnts[i].first - last);
        
        ll dp0 = dp[0].back(), dp1 = dp[1].back(), dp2 = dp[2].back();
        for (int j = 0; j < 3; j++) {
            dp[j].push_back(m[j][0] * dp0 + m[j][1] * dp1 + m[j][2] * dp2);
        }

        if (evnts[i].second >= 0) {
            blck[evnts[i].second] ^= 1;
            if (blck[evnts[i].second]) dp[evnts[i].second].back() = 0;
        }
        last = evnts[i].first;

        // cout << evnts[i].first << " " << dp[0].back() << " " << dp[1].back() << " " << dp[2].back() << endl;
    }

    cout << dp[1].back();
}