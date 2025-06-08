// https://codeforces.com/contest/1978/problem/D

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

// Using a custom comparator to sort candidates such that the winning candidate is first
struct comp {
    bool operator() (plli a, plli b) {
        if (a.first != b.first)
            return a.first > b.first;
        // If any 2 candidates have the same # of votes, smaller index wins
        return a.second < b.second;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        ll c;
        cin >> N >> c;

        ll a[N], rempre[N + 1];
        rempre[0] = 0;
        ordered_multiset omst;

        for (int i = 0; i < N; i++) {
            cin >> a[i];
            rempre[i + 1] = rempre[i] + a[i];

            if (i > 0) omst.insert({a[i], i});
            else omst.insert({a[i] + c, i});
        }

        for (int i = 0; i < N; i++) {
            auto most = omst.find_by_order(0);
            if (most->second == i) {
                // If this candidate already wins then just print 0
                cout << 0 << " ";
                continue;
            } 

            // Otherwise, to add votes to this candidate we must get rid of all the candidates before it
            ll added = rempre[i] + c;
            // Note that after removing all the candidates before it, this will be the first candidate
            ll rem = i;

            // If we already have enough voters from the candidates before and the undecided people then thats enough
            // However, in the case that we don't
            // All we need to do to make this the best candidate is get rid of the current candidate with the max voters
            // As that will give us the most voters
            // And if we tie with another candidate, we are the first one so we will win
            if (added + a[i] < most->first) {
                // No need to calculate the extra votes added
                // as we know that this is all we need
                rem++;
            }

            cout << rem << " ";
        }

        cout << endl;
    }
}