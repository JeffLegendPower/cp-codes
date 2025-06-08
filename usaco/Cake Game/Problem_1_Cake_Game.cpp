// https://usaco.org/index.php?page=viewproblem&cpid=1434

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define plli pair<ll, int>
#define pll pair<ll, ll>
#define pii pair<int, int>


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;

        ll a[N];
        ll total = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            total += a[i];
        }

        // Bessie maximizing her score is the same as minimizing Elsie's score, and the same applies for Elsie
        // Bessie plays n/2 times and Elsie n/2 - 1 times
        // Elsie can pick n/2 - 1 elements from the left and right to maximize her score
        // And Bessie gets the other n/2 + 1 elements
        // Bessie has to always pick the middle 2 elements, as those are "unreachable" by Elsie in n/2 - 1 turns
        // Essentially, over all x < N/2, Bessie's score is the minimum of a[x..x+n/2]
        // where a[x..y] is the sum of all elements of a between x and y
        // If Bessie tries not to pick the middle 2 elements, Bessie is never making the situation better for herself
        // only potentially making one of Elsie's choices resulting in more cake
        // So we can assume that Bessie picks the middle 2

        ll summ = 0;
        for (int i = 0; i < N/2; i++) summ += a[i];

        ll bessie = 1e18;
        for (int i = N/2; i < N; i++) {
            summ += a[i];
            bessie = min(bessie, summ);
            summ -= a[i - N/2];
        }

        cout << bessie << " " << total - bessie;
        if (T > 0) cout << endl;
    }
}