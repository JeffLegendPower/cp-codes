// https://codeforces.com/contest/1935/problem/D

// This can be solved using the inclusion exclusion principle
// Ignoring the set, the total number of pairs is (c + 1) * (c + 2) / 2
// As there are c + 1 values of y [0..c], and for each value of y there are y possible x values
// Now look at each element in the set independently, there are 1 + c - (s[i] + 1) / 2 pairs which would
// trigger the condition for that element. As there are c + 1 values of y, all of the values of y
// above s[i] has a unique x which triggers the condition, but only the values of y below s[i] that have an x
// which sums to s[i] would trigger the condition
// So we remove all those extra pairs
// Now we might overcount a pair when removing it, so we need to add that back
// For each pair of elements in the set, s[i] and s[j] where i < j, they intersect at most once
// s[i] and s[j] will have an intersection if s[j] - s[i] is even
// This is true because if there exists an intersection between those 2, it will look like this system
// y + x = s[j], y - x = s[i] => s[j] - 2x = s[i] => 2x = s[j] - s[i] => x = (s[j] - s[i]) / 2
// For x to be an integer, s[j] - s[i] has to be even
// So now a counter can be held for the number of odd and even elements before the current element
// And add those back to the total to include what was excluded twice


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
        ll c;
        cin >> N >> c;

        ll s[N];
        for (int i = 0; i < N; i++) cin >> s[i];
        
        ll total = (c + 1) * (c + 2) / 2;

        int numOdd = 0, numEven = 0;
        for (int i = 0; i < N; i++) {
            ll minval = (s[i] + 1) / 2;
            total -= c - minval + 1;
            if (s[i] % 2 == 0) total += numEven++;
            else total += numOdd++;
        }

        cout << total << endl;
    }
}