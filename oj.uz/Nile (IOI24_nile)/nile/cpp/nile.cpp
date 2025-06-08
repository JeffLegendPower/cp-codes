// Problem link here: https://oj.uz/problem/view/IOI24_nile

// #include "nile.h"

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

struct artif {
    ll A, B, W;
};

// ll solveQ(vector<ll> &W, vector<ll> &A, vector<ll> &B, vector<ll> &E) {
ll solveQ(vector<artif> &facts, ll D, int N) {

    vector<ll> dp(N + 1, 0);
    dp[1] = facts[0].A;

    int l = 0;
    ll totalB = 0;
    deque<ll> minsave;

    // for (int r = 0; r < N; r++) {
    //     dp[r + 1] = dp[r] + facts[r].A;

    //     while (facts[l].W - facts[r].W > D) {
    //         totalB -= facts[l].B;

    //         ll save = facts[l].A - facts[l].B;
    //         if (!minsave.empty() && minsave.front() == save) minsave.pop_front();

    //         l++;
    //     }

    //     int diff = r - l;
    //     ll cost = dp[l] + facts[r].B + facts[l].B + totalB;
    //     if (diff&1) cost += minsave.front();

    //     dp[r + 1] = min(dp[r + 1], dp[l] + cost);
    // }

    for (int i = 1; i < N; i++) {
        dp[i + 1] = dp[i] + facts[i].A;

        ll totalB = 0;
        ll minsave = 1e18;
        for (int j = i - 1; j >= 0; j--) {
            if (facts[j].W - facts[i].W > D) break;
            int diff = i - j - 1;
            
            ll cost = facts[i].B + facts[j].B + totalB;
            if (diff&1) cost += minsave;

            dp[i + 1] = min(dp[i + 1], dp[j] + cost);

            totalB += facts[j].B;
            minsave = min(minsave, facts[j].A - facts[j].B);
        }
    }

    for (int i = 1; i <= N; i++) cout << dp[i] << " ";
    cout << endl;

    return dp[N];
}

// std::vector<long long> calculate_costs(std::vector<int> W, std::vector<int> A, std::vector<int> B, std::vector<int> E) {
//     int Q = (int) E.size();
//     std::vector<long long> R(Q, 0);

//     int N = (int) W.size();

//     vector<artif> facts(N);
//     for (int i = 0; i < N; i++) {
//         facts[i].W = W[i];
//         facts[i].A = A[i];
//         facts[i].B = B[i];
//     }

//     sort(facts.begin(), facts.end(), [](artif one, artif two) {
//         return one.W > two.W;
//     });

//     for (int q = 0; q < Q; q++) {
//         R[q] = solveQ(facts, E[q], N);
//     }

//     return R;
// }

int main() {
    int N; cin >> N;

    vector<artif> facts(N);
    for (int i = 0; i < N; i++) cin >> facts[i].W >> facts[i].A >> facts[i].B;

    sort(facts.begin(), facts.end(), [](artif one, artif two) {
        return one.W > two.W;
    });

    int Q; cin >> Q;

    while (Q--) {
        ll D; cin >> D;

        cout << solveQ(facts, D, N) << endl;

        // vector<ll> dp(N + 1, 0);
        // dp[1] = facts[0].A;

        // for (int i = 1; i < N; i++) {
        //     dp[i + 1] = dp[i] + facts[i].A;

        //     ll totalB = 0;
        //     ll minsave = 1e18;
        //     for (int j = i - 1; j >= 0; j--) {
        //         if (facts[j].W - facts[i].W > D) break;
        //         int diff = i - j - 1;
                
        //         ll cost = facts[i].B + facts[j].B + totalB;
        //         if (diff&1) cost += minsave;

        //         dp[i + 1] = min(dp[i + 1], dp[j] + cost);

        //         totalB += facts[j].B;
        //         minsave = min(minsave, facts[j].A - facts[j].B);
        //     }
        // }

        // cout << dp[N] << endl;
        // for (int i = 1; i <= N; i++) cout << dp[i] << " ";
    }
}