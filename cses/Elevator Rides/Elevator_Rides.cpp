// https://cses.fi/problemset/task/1653

// Naively, we'd solve this in O(n!) by testing every ordering of people
// and seeing what works in the minimal number of elevator rides
// However, we can solve this using subsets and bitmasks
// Each bit can represent whether a person is included in the subset
// And we can hold an array for the bitmask which says how many elevator rides
// are needed, and the current weight of the last elevator ride for the subset
// Now to calculate the dp state for a subset, we will exclude each person i
// from the subset (if it's in it) so S \ {i} and then fetch the dp state of
// that previous subset and add the weight of person i to it, and if the weight
// exceeds the limit, then move person i over and increase the elevator count by 1
// and then pick the minimum elevator count and then the minimum weight of the last elevator
// So we need to first calculate all subsets with 1 person, then 2 people, and so on
// This will result in us solving this in O(n*2^n)

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
    int N;
    ll x;
    cin >> N >> x;

    ll weights[N];
    for (int i = 0; i < N; i++) cin >> weights[i];

    // weight of the rightmost elevator ride, number of elevator rides
    vector<plli> subsets;
    for (ll i = 0; i < (1ll << N); i++) subsets.push_back({0ll, 100});

    for (int k = 0; k <= N; k++) {
        for (ll msk = 0; msk < (1ll << N); msk++) {
            if (__builtin_popcount(msk) != k)
                continue;

            if (msk == 0) {
                subsets[msk] = {x, 0};
                continue;
            }

            for (int rem = 0; rem <= N; rem++) {
                // cout << msk << endl;
                ll prev = msk ^ (1ll << rem);
                if (prev > msk) continue;

                plli cur = {subsets[prev].first + weights[rem], subsets[prev].second};
                if (cur.first > x) {
                    cur.first = weights[rem];
                    cur.second++;
                }

                if (cur.second < subsets[msk].second) subsets[msk] = cur;
                else if (cur.second == subsets[msk].second && cur.first < subsets[msk].first) subsets[msk] = cur;
            }
        }
    }
    
    cout << subsets[(1ll<<N) - 1].second << endl;
}