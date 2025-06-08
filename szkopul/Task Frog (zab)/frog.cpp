// https://szkopul.edu.pl/problemset/problem/qDH9CkBHZKHY4vbKRBlXPrA7/site/?key=statement

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


ll p[1000000];

int num(int i, ll k, int N) {
    int ans = 0;
    int low = i, high = N - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (p[mid] - p[i] <= k) {
            ans = mid - i + 1;
            low = mid + 1;
        } else high = mid - 1;
    }

    low = 0, high = i - 1;
    int best = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (p[i] - p[mid] <= k) {
            best = i - mid;
            high = mid - 1;
        } else low = mid + 1;
    }

    return ans + best;
}

int jmp[2][1000000];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, K;
    ll M;
    cin >> N >> K >> M;

    map<ll, int> mapp;
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        mapp[p[i]] = i;
    }

    for (int i = 0; i < N; i++) {
        ll low = 0, high = 1e18;
        ll best = 1e18;
        while (low <= high) {
            ll mid = low + (high - low) / 2;
            int cnt = num(i, mid, N);
            if (cnt > K) {
                high = mid - 1;
                best = mid;
            } else low = mid + 1;
        }

        if (mapp.find(p[i] - best) == mapp.end()) jmp[0][i] = mapp[p[i] + best];
        else jmp[0][i] = mapp[p[i] - best];
    }

    vector<int> anss(N); for (int i = 0; i < N; i++) anss[i] = i;

    for (int b = 0; b < 60; b++) {
        for (int i = 0; i < N; i++) jmp[(b&1)^1][i] = jmp[b&1][jmp[b&1][i]];
        if (!(M&(1ll<<b))) continue;
        for (int i = 0; i < N; i++) {
            int x = anss[i];

            anss[i] = jmp[b&1][anss[i]];
        }
    }

    for (int i = 0; i < N; i++) {

        cout << anss[i]+1 << " ";
    }
}