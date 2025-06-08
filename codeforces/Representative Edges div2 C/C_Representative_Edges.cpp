// https://codeforces.com/contest/1616/problem/C

// The only way to satisfy the conditions is by having a
// Constant, increasing with a constant difference, or decreasing with a constant difference (can be any real number)
// So we can go through each element of a and use it as a pivot point (don't change it)
// And then we need to use a second pivot point to create constant differences to check, as this makes
// worst case n - 2 operations needed, and if we find a common difference such that we need < n - 2 operations,
// It will still pass through atleast 2 points which we would've tested for
// Time compexity ~O(n^3)
// As n elements, need to test every pair of pivot points (n * n) and iterate through the array per test (n)

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        double a[N];
        for (int i = 0; i < N; i++) cin >> a[i];

        int opermax = 1e5;

        if (N == 1) opermax = 0;

        // Try each pivot point
        for (int i = 0; i < N; i++) {
            // Try a second pivot point
            for (int j = i + 1; j < N; j++) {

                // Now we have our common difference
                double diff = (a[j] - a[i]) / (j - i);

                // Now iterate through the array to see how many operations to fit this common difference
                int operations = 0;
                for (int k = 0; k < N; k++) {
                    double expected = a[i] + (k - i) * diff;

                    // Stupid ass double shit
                    if (abs(a[k] - expected) > 0.0001) operations++;
                }

                opermax = min(opermax, operations);
            }
        }

        cout << opermax << endl;
    }
}