// https://codeforces.com/contest/1957/problem/D

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

        ll a[N];
        int bitspre[N + 1][32], evenlens[N + 1][32], oddlens[N + 1][32];
        int evensuff[N + 1][32], oddsuff[N + 1][32], bitssuff[N + 1][32];
        for (int i = 0; i < 32; i++) {
            bitspre[0][i] = 0;
            evenlens[0][i] = 0;
            oddlens[0][i] = 0;

            evensuff[N][i] = 0;
            oddsuff[N][i] = 0;
            bitssuff[N][i] = 0;

            // afterOdd[i] = 0;
            // afterEven[i] = 0;
            // beforeOdd[i] = 0;
            // beforeEven[i] = 0;
        }

        for (int i = 0; i < N; i++) {
            cin >> a[i];
            for (ll j = 0; j < 32; j++) {
                bitspre[i + 1][j] = bitspre[i][j];
                evenlens[i + 1][j] = evenlens[i][j];
                oddlens[i + 1][j] = oddlens[i][j];
                if ((a[i] & (1ll << j)) > 0) bitspre[i + 1][j]++;
                if (bitspre[i + 1][j] % 2 == 0) evenlens[i + 1][j]++;
                else oddlens[i + 1][j]++;
                // if (bitspre[i + 1][j] % 2 == 0) afterEven[j]++;
                // else afterOdd[j]++;
            }
        }
        for (int i = N - 1; i >= 0; i--) {
            for (ll j = 0; j < 32; j++) {
                evensuff[i][j] = evensuff[i + 1][j];
                oddsuff[i][j] = oddsuff[i + 1][j];
                bitssuff[i][j] = bitssuff[i + 1][j];
                if ((a[i] & (1ll << j)) > 0) bitssuff[i][j]++;
                if (bitssuff[i][j] % 2 == 0) evensuff[i][j]++;
                else oddsuff[i][j]++;

            }
        }

        ll total = 0;

        for (int i = 0; i < N; i++) {
            ll mostsigbit = 0;
            for (ll j = 0; j < 32; j++) {
                if ((a[i] & (1ll << j)) > 0) {
                    mostsigbit = j;
                }
            }

            // ll after = bitspre[N][mostsigbit] - bitspre[i + 1][mostsigbit];
            // ll before = bitspre[i][mostsigbit];

            // How many ways can we combine these 2 numbers such that the sum of their parts is odd?
            // The "1 +" for even is because we also have to account for 0
            ll afterOdd = oddlens[N][mostsigbit] - oddlens[i + 1][mostsigbit], afterEven = evenlens[N][mostsigbit] - evenlens[i + 1][mostsigbit];
            // ll beforeOdd = oddlens[i][mostsigbit], beforeEven = evenlens[i][mostsigbit];
            ll beforeOdd = oddsuff[0][mostsigbit] - oddsuff[i][mostsigbit], beforeEven = evensuff[0][mostsigbit] - evensuff[i][mostsigbit];
            if (bitssuff[i][mostsigbit] % 2 == 1) {
                ll temp = beforeOdd;
                beforeOdd = beforeEven;
                beforeEven = temp;
            }

            total += afterOdd * beforeEven + beforeOdd * afterEven + beforeOdd + afterOdd;
            // cout << (afterOdd * beforeEven + beforeOdd * afterEven + beforeOdd + afterOdd) << endl;
            // cout << afterOdd << " " << afterEven << " " << beforeOdd << " " << beforeEven << endl;
        }

        cout << total << endl;
    }
}