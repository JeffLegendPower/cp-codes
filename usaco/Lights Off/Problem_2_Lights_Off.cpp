// https://usaco.org/index.php?page=viewproblem2&cpid=1282

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


bool dp[1<<20][41];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T, N;
    cin >> T >> N;

    dp[0][0] = true;

    for (int i = 0; i < 2*N; i++) {
        for (int msk = 0; msk < 1<<N; msk++) {
            // int t = dp[msk][i];
            if (!dp[msk][i]) continue;

            int tmod = (i+1)%(2*N);
            int t = i+1;

            // need to optimize this to just 1 loop
            // can do by doing the update for b=0, and then for each b we can just flip 2 bits
            int msk2 = msk;

            if (tmod < N) {
                msk2 ^= (1 << tmod) - 1;
            } else {
                int r = tmod - N;
                msk2 ^= ((1 << N) - 1) - ((1 << r) - 1);
            }

            dp[msk2][t] = true;

            for (int b = 1; b < N; b++) {
                msk2 ^= 1<<(b-1);
                msk2 ^= 1<<((b+tmod-1)%N);

                dp[msk2][t] = true;
            }
        }
    }

    while (T--) {
        string A, B;
        cin >> A >> B;

        int a = 0, b = 0;
        for (int i = 0; i < N; i++) if (A[i] == '1') a ^= 1<<i;
        for (int i = 0; i < N; i++) if (B[i] == '1') b ^= 1<<i;

        if (dp[a][0]) {
            cout << 0 << endl;
            continue;
        }

        bool done = false;
        for (int tmod = 1; tmod < 2*N; tmod++) {
            // take first N - (tmod-1)%N bits of b, shift them to the right by (tmod-1)%N, and apply that to a
            int msk = (1<<(N - (tmod-1)%N)) - 1;
            a ^= (b&msk)<<((tmod-1)%N);

            // take the other bits, and shift them left by N - (tmod-1)%N and apply that to a
            int b2 = b^(b&msk);
            a ^= b>>(N - (tmod-1)%N);

            if (dp[a][tmod]) {
                cout << tmod << endl;
                done = true;
                break;
            }
        }

        if (!done) cout << 2*N << endl;
    }
}