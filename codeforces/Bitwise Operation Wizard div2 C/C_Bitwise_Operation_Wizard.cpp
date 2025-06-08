// https://codeforces.com/contest/1937/problem/C

// We can solve this with the key observation that
// The max XOR of the array will be 111...
// Where the size is that of the most significant bit of n - 1
// We can also always construct this XOR using n - 1
// The index of n - 1 can be found by iterating through p
// Keep track of the current max index, since a OR a = a,
// We can compare p[max index] OR p[max index] and p[i] OR p[i]
// If i OR i is greater, we set that to the new max index
// Now, there is exactly one other index that can XOR with n - 1 to make 111...
// However, there are multiple indices that can OR with n - 1 to make 111...
// So we will find all of these indices, by again iterating through the array
// But this time we will keep a vector of the best indices
// However, if we go through an i such that n - 1 OR p[i] > n - 1 OR p[known max]
// Then we need to clear the array (removing at most n elements in total) and start tracking again
// Now that we have the list of indices such that n - 1 OR p[i] = 111...
// Only one of them will work for XOR, and that will be the minimum of them
// This is because all of them will atleast have the essential bits to make n - 1 OR p[i] = 111...
// But any of those that have extra bits will not satisfy it for XOR, and they will all be greater than the
// one that only has the essential bits. So now we can use the same technique to find n - 1
// to find the min of our list of valid indices

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


struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 1e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int maxIdx = 0;
        for (int i = 1; i < N; i++) {
            cout << "? " << (maxIdx) << " " << (maxIdx) << " " << (i) << " " << (i) << endl;

            char response;
            cin >> response;
            if (response == '<') maxIdx = i;
        }

        vector<int> validIdxs;
        if (maxIdx == 0) validIdxs.push_back(1);
        else validIdxs.push_back(0);
        for (int i = 0; i < N; i++) {
            if (i == maxIdx || i == validIdxs.back()) continue;
            cout << "? " << (maxIdx) << " " << (validIdxs.back()) << " " << (maxIdx) << " " << (i) << endl;

            char response;
            cin >> response;
            if (response == '<') {
                validIdxs.clear();
                validIdxs.push_back(i);
            } else if (response == '=') {
                validIdxs.push_back(i);
            }
        }

        int targetIdx = validIdxs[0];
        for (int i = 1; i < validIdxs.size(); i++) {
            cout << "? " << (targetIdx) << " " << (targetIdx) << " " << (validIdxs[i]) << " " << (validIdxs[i]) << endl;

            char response;
            cin >> response;
            if (response == '>') targetIdx = validIdxs[i];
        }

        cout << "! " << targetIdx << " " << maxIdx << endl;
    }
}