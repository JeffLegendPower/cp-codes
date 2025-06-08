// https://codeforces.com/contest/1700/problem/C

// We need to first notice that we just need to get all the elements equal to eachother
// Then we can increment/decrement the entire array to 0
// To do this we will look at the differences between a[i] and a[i + 1] (a[i + 1] - a[i])
// If diff > 0, then a[i + 1] > a[i] and we need to decrement the suffix including a[i + 1] by diff
// If diff < 0, then a[i] > a[i + 1] and we need to decrement the prefix including a[i] by diff
// Finally, all the elements will be the same so we will need to add abs(final value) to our operations
// as we still need to make the array a equal to 0

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

        ll a[N];

        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }

        ll oper = 0;
        ll end = a[0];

        for (int i = 0; i < N - 1; i++) {
            ll diff = a[i + 1] - a[i];
            if (diff > 0) oper += diff;
            else if (diff < 0) {
                oper += -diff;
                end += diff;
            }
        }

        cout << oper + abs(end) << endl;
    }
}