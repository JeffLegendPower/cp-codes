// https://cses.fi/problemset/task/1745

// Now although this may look like it takes O(2^n) time
// Notice that the maximum sum we can have is 100000 (1e5)
// So this is more like O(sum(X)) time at most
// This can be done with a set as it only stores unique elements
// So if we have a duplicate it will automatically discard it
// For each element x we can iterate through the set s
// And insert back into the set x + s[i]
// Make sure to iterate backwards though, as otherwise if we add an element to a set which is greater, then
// the set becomes longer forwards and we would be looping forever and infinitely duplicating entries
// And also insert x into the set after that as we can make a sum from just x
// But do that after iterating through the set, as otherwise we would be also inserting x+x into the set
// which is a duplicate and not always possible

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
    cin >> N;

    set<ll> sums;

    for (int i = 0; i < N; i++) {
        ll x;
        cin >> x;
        for (auto itr = sums.rbegin(); itr != sums.rend(); itr++) {
            sums.insert(*itr + x);
        }
        sums.insert(x);
    }

    cout << sums.size() << endl;
    for (auto itr = sums.begin(); itr != sums.end(); itr++) cout << *itr << " ";
}