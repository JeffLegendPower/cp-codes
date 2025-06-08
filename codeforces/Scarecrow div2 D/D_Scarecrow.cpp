// https://codeforces.com/contest/2055/problem/D

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

#define ld long double

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N;
        ld k, l;
        cin >> N >> k >> l;

        ld pos = 0;

        ld s[N];
        for (int i = 0; i < N; i++) {
            cin >> s[i];
        }

        ld t = 0;

        if (s[0] > 0) {
            t += s[0];
            s[0] = 0;
            pos = k;
        }

        ld ans = 1e9;
        for (int i = 0; i < N; i++) {
            pos = max(pos, s[i] + k);
            if (pos >= l) {
                ans = min(ans, t);
                break;
            }

            ans = min(ans, l - k - s[i] + t);
            if (i == N - 1) {
                break;
            }

            if (s[i+1] <= pos) s[i+1] = min(s[i+1] + t, pos);
            if (s[i+1] >= pos) s[i+1] = max(s[i+1]-t, pos);

            if (s[i+1] <= pos) {
                continue;
            }
            
            ld tim = (s[i+1] - s[i] - k) / 2;
            pos += tim;
            s[i+1] = pos;
            t += tim;

            if (pos >= l) {
                ans = min(ans, t);
                break;
            }
        }
        
        cout << llround(2*ans) << endl;
    }
}