// https://codeforces.com/contest/2064/problem/D

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, Q; cin >> N >> Q;

        ll w[N]; for (int i = 0; i < N; i++) cin >> w[i];

        ll wpre[N+1];
        wpre[0] = 0;
        for (int i = 0; i < N; i++) wpre[i+1] = wpre[i]^w[i];

        // msbi[i][j] = rightmost w index i with msb j
        int msbi[N][30];
        for (int i = 0; i < N; i++) {
            for (int b = 0; b < 30; b++) {
                if (i > 0) msbi[i][b] = msbi[i-1][b];
                else msbi[i][b] = -1;
            }

            for (int b = 29; b >= 0; b--) {
                if (w[i]&(1ll<<b)) {
                    msbi[i][b] = i;
                    break;
                }
            }
        }

        while (Q--) {
            ll x; cin >> x;

            int i = N-1;

            while (x > 0 && i >= 0) {
                int msbx = -1;
                for (int b = 29; b >= 0; b--) {
                    if (x&(1ll<<b)) {
                        msbx = b;
                        break;
                    }
                }

                int widx = msbi[i][msbx];
                int killidx = -1;
                for (int b = 29; b > msbx; b--) {
                    if (msbi[i][b] > widx) {
                        killidx = max(killidx, msbi[i][b]);
                    }
                }

                if (killidx != -1) {
                    i = killidx;
                    goto end;
                }

                if (widx == -1) {
                    i = -1;
                    goto end;
                }

                ll wi = w[widx];
                x = x^wpre[i+1]^wpre[widx+1];

                if (wi > x) {
                    i = widx;
                    goto end;
                }

                x ^= wi;
                i = widx - 1;
            }

            end:
            cout << (N-1-i) << " ";
        }

        cout << endl;
    }
}