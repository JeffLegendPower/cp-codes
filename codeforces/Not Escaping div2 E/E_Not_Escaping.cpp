// https://codeforces.com/contest/1627/problem/E

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

struct ladder {
    int a, b, c, d;
    ll h;

    ll dp = -1;
    ll left = -1, right = -1;
    bool impossible = false, impossibleleft = false, impossibleright = false;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<ladder> lds[N];
        ll x[N];
        for (int i = 0; i < N; i++) cin >> x[i];

        for (int i = 0; i < K; i++) {
            ladder ld;
            cin >> ld.a >> ld.b >> ld.c >> ld.d >> ld.h;
            ld.a--, ld.b--, ld.c--, ld.d--;

            lds[ld.a].push_back(ld);
        }

        for (int i = 0; i < N; i++) {
            sort(lds[i].begin(), lds[i].end(), [](ladder one, ladder two) {
                return one.b < two.b;
            });
        }

        for (int i = N - 1; i >= 0; i--) {
            for (ladder &ld : lds[i]) {
                if (ld.c == N - 1) {
                    ld.dp = x[N-1]*abs(M - 1 - ld.d) - ld.h;
                    continue;
                }

                if (lds[ld.c].size() == 0) {
                    ld.impossible = true;
                    continue;
                }

                int low = 0, high = lds[ld.c].size() - 1;
                int best = -1;
                while (low <= high) { 
                    int mid = low + (high - low) / 2;

                    if (lds[ld.c][mid].b > ld.d) high = mid - 1;
                    else {
                        low = mid + 1;
                        best = mid;
                    }
                }

                if (best == -1) {
                    if (lds[ld.c][0].impossibleleft) {
                        ld.impossible = true;
                        ld.dp = 1e18;
                        continue;
                    }
                    ld.dp = lds[ld.c][0].left - x[ld.c] * ld.d;
                } else {
                    ld.impossible = true;
                    ld.dp = 1e18;
                    if (!lds[ld.c][best].impossibleright) {
                        ld.dp = lds[ld.c][best].right - x[ld.c] * (M-1 - ld.d);
                        ld.impossible = false;
                    }

                    if (best < lds[ld.c].size() - 1 && !lds[ld.c][best+1].impossibleleft) {
                        ld.dp = min(ld.dp, lds[ld.c][best+1].left - x[ld.c] * ld.d);
                        ld.impossible = false;
                    }
                }
            }

            for (int j = 0; j < lds[i].size(); j++) {
                if (lds[i][j].impossible) {
                    lds[i][j].right = 1e18;
                    lds[i][j].impossibleright = true;
                } else lds[i][j].right = lds[i][j].dp + x[i] * (M-1 - j);

                if (j > 0) {
                    lds[i][j].right = min(lds[i][j].right, lds[i][j-1].right);
                    if (!lds[i][j-  1].impossibleright) lds[i][j].impossibleright = false;
                }
            }

            for (int j = lds[i].size() - 1; j >= 0; j--) {
                if (lds[i][j].impossible) {
                    lds[i][j].left = 1e18;
                    lds[i][j].impossibleleft = true;
                } else lds[i][j].left = lds[i][j].dp + x[i] * j;

                if (j < lds[i].size() - 1) {
                    lds[i][j].left = min(lds[i][j].left, lds[i][j+1].left);
                    if (!lds[i][j+1].impossibleleft) lds[i][j].impossibleleft = false;
                }
            }
        }

        bool possible = false;
        ll ans = 1e18;
        for (ladder &ld : lds[0]) {
            if (!ld.impossibleleft) {
                possible = true;
                ans = min(ans, ld.left);
            }
        }

        if (!possible) cout << "NO ESCAPE" << endl;
        else cout << ans << endl;
    }
}