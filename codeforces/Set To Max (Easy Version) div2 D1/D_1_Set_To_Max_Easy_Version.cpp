// https://codeforces.com/contest/1904/problem/D1

// We can check for each index to see if we can satisfy the condition
// For the obvious case if a[i] > b[i] it won't work
// Now, we will look to the left and to the right
// If we find our desired max, that's good
// However, in the direction we are going if we find an element a[j] too big then we can't use that direction
// As it will make the number too big
// Same if we cross another b[j] that's smaller than what we are looking for, we would be setting a[j] to
// a number too big, which would make that direction not work

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

        int a[N];
        int b[N];
        for (int i = 0; i < N; i++) cin >> a[i];
        for (int i = 0; i < N; i++) cin >> b[i];

        bool works = true;

        for (int i = 0; i < N; i++) {
            if (a[i] == b[i]) continue;

            if (a[i] > b[i]) {
                works = false;
                break;
            }

            bool found = false;
            for (int j = i - 1; j >= 0; j--) {
                // We are able to get a max that will let us satisfy the condition for this index
                if (a[j] == b[i]) found = true;
                // We can't get a max from this direction as it will make the condition fail for another index
                if (b[j] < b[i]) break;
                // A max from this direction would be too big and would make the condition fail for this index
                if (a[j] > b[i]) break;
            } for (int j = i + 1; j < N; j++) {
                // We are able to get a max that will let us satisfy the condition for this index
                if (a[j] == b[i]) found = true;
                // We can't get a max from this direction as it will make the condition fail for another index
                if (b[j] < b[i]) break;
                // A max from this direction would be too big and would make the condition fail for this index
                if (a[j] > b[i]) break;
            }

            if (!found) {
                works = false;
                break;
            }
        }

        cout << (works ? "YES" : "NO") << endl;
    }
}