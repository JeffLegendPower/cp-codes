// https://dmoj.ca/problem/ioi05p4

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

const int MAXN = 1e6;
int p[MAXN], p2[MAXN], times[MAXN];
bool dir[MAXN];

bool clockrem[2*MAXN], anticlockrem[2*MAXN];

int solve(int N) {
    for (int i = 0; i < N; i++) p2[p[i]-1] = i;
    for (int i = 0; i < 2*N; i++) {
        clockrem[i] = false;
        anticlockrem[i] = false;
    }
    // set<int, greater<int>> clock, anticlock;

    priority_queue<int> clock, anticlock;

    // {time, idx}
    priority_queue<pii, deque<pii>, greater<pii>> events;

    for (int i = 0; i < N; i++) {
        if ((N + p2[i] - i)%N < (N + i - p2[i])%N) {
            clock.push((N + p2[i] - i)%N);

            times[i] = (N + p2[i] - i)%N;
            dir[i] = true;

            events.push({(N + i - p2[i])%N - N/2, i});
        } else {
            anticlock.push((N + i - p2[i])%N);

            times[i] = (N + i - p2[i])%N;
            dir[i] = false;

            events.push({(N + i - p2[i])%N, i});
        }
    }

    int best = 1e8;
    for (int i = 0; i < N; i++) {
        while (events.top().first == i) {
            auto [t, idx] = events.top();
            events.pop();



            if (!dir[idx]) {
                // if (anticlockrem[times[idx] + N]) continue;
                // anticlock.erase(times[idx]);
                anticlockrem[times[idx] + N] = true;

                dir[idx] = true;
                times[idx] = -i;
                clock.push(-i);

                events.push({N - N/2 + i, idx});
            } else {
                // if (clockrem[times[idx] + N]) continue;
                // clock.erase(times[idx]);
                clockrem[times[idx] + N] = true;

                dir[idx] = false;
                times[idx] = N/2 + i;
                anticlock.push(N/2 + i);

                events.push({N/2 + i, idx});
            }
        }

        while (!clock.empty() && clockrem[clock.top() + N]) clock.pop();
        while (!anticlock.empty() && anticlockrem[anticlock.top() + N]) anticlock.pop();

        int time = 0;
        if (!clock.empty()) time = max(time, clock.top() + i);
        if (!anticlock.empty()) time = max(time, anticlock.top() - i);

        best = min(best, time);
    }

    return best;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;

    for (int i = 0; i < N; i++) cin >> p[i];
    

    int ans = solve(N);
    for (int i = 0; i < N/2; i++) swap(p[i], p[N-1-i]);
    ans = min(ans, solve(N));

    cout << ans;
}