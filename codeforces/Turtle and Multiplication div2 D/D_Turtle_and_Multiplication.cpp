// https://codeforces.com/contest/1981/problem/D
// Another fail :(

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

        if (N < 5) {
            for (int i = 0; i < N; i++) {
                cout << (i / 2 + 1) << " ";
            }
            cout << endl;
        }
    }
}