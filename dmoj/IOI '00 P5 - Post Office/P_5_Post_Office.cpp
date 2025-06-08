// https://dmoj.ca/problem/ioi00p5

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

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;no


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, P;
    cin >> N >> P;

    int V[N];
    int pre[N+1], suff[N+1];
    pre[0] = 0;
    suff[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> V[i];
        pre[i+1] = pre[i] + V[i];
        suff[i+1] = suff[i] + V[N-1] - V[i];
    }

    int dp[N][P];
    pii dp2[N][P];
    int ans = 1e9;
    pii ans2 = {-1, -1};
    for (int i = 0; i < N; i++) {
        dp[i][0] = V[i]*i - pre[i];
        dp2[i][0] = {-1, -1};

        int totalcost = dp[i][0] + pre[N] - pre[i+1] - V[i]*(N-i-1);
        if (totalcost < ans) {
            ans = totalcost;
            ans2 = {i, 0};
        }
    }

    for (int p = 1; p < P; p++) {
        for (int i = 0; i < N; i++) dp[i][p] = 1e9;
        for (int i = p; i < N; i++) {
            int mididx = i;
            for (int j = i-1; j >= p-1; j--) {
                // idxs j to mididx will go to the left
                // and idxs mid+1 to i will go right
                int mid = (V[j]+V[i])/2;
                while (V[mididx] > mid) mididx--;

                int cost = dp[j][p-1] + (pre[mididx+1]-pre[j] - V[j]*(mididx-j+1)) + (V[i]*(i-mididx) - pre[i+1]+pre[mididx+1]);
                if (cost < dp[i][p]) {
                    dp[i][p] = cost;
                    dp2[i][p] = {j, p-1};
                }

                int totalcost = dp[i][p] + pre[N] - pre[i+1] - V[i]*(N-i-1);
                if (totalcost < ans) {
                    ans = totalcost;
                    ans2 = {i, p};
                }
            }
        }
    }

    cout << ans << endl;
    vector<int> pos;
    while (ans2.first != -1) {
        pos.push_back(V[ans2.first]);
        ans2 = dp2[ans2.first][ans2.second];
    }
    reverse(pos.begin(), pos.end());

    for (int loc : pos) cout << loc << " ";
}