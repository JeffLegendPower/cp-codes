// https://codeforces.com/contest/1944/problem/C

// We can make a frequency array (or here I used a map and multiset) for the frequency of each number
// If freq[number] >= 2, even if Bob tries removing it Alice can just take it and add it to c
// However, if freq[number] == 1, then if Bob takes it Alice can't anymore
// Since Alice goes first, it will be better for her to take the lowest number such that freq[number] == 1
// And then Bob will take the second lowest number such that freq[number] == 1, capping the MEX
// So we can then calculate the MEX without removing anything and then take the minimum of that and the second number
// such that freq[number] == 1 and that will be the answer

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

struct comp {
    bool operator() (plli a, plli b) {
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        // Frequency array (or here map)
        map<int, int> a;
        for (int i = 0; i < N; i++) {
            int ai;
            cin >> ai;
            a[ai]++;
        }

        // Putting everything into an ordered multiset
        // It will auto sort by freq in ascending order and then element number in ascending order
        ordered_multiset omst;
        for (auto itr = a.begin(); itr != a.end(); itr++) {
            omst.insert({ itr->second, itr->first });
        }

        // Calculate MEX without any removals (note this must be done after inserting everything into the omst
        // as this adds an entry into the map where the freq[element] = 0)
        int mex = 0;
        while (a[mex] > 0) {
            mex++;
        }

        // If there's only 1 unique element in all of a, then Alice will take that and that's it
        if (omst.size() < 2) {
            cout << mex << endl;
            continue;
        }

        // Find the second element
        auto second = omst.find_by_order(1);

        // If Bob can prevent Alice from taking it, we take the min of the mex and that element
        // Otherwise Alice will be able to take it and we just print the mex
        if (second->first == 1) {
            cout << min(mex, second->second) << endl;
        } else cout << mex << endl;
    }
}