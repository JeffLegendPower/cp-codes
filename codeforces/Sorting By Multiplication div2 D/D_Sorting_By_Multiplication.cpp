// https://codeforces.com/contest/1861/problem/D

// First we need to notice that we can do our operations in any order
// As multiplication is communative
// Second, since every number is originally positive
// We can only apply negative operations
// in such a way that its in the prefix of our array
// So we can iterate through the negative prefix of the array
// As we just can multiply that by -1 (make sure to account for that operations)
// And notice that by multiplying a prefix (to fix the negative part) or a suffix (to fix the positive part)
// We can only fix one inequality
// So we need to count the number of inequalities such that a[i] <= a[i + 1] for all i > the negative part
// and the number of inequalities (in the original array) such that a[i - 1] <= a[i] for all 0 < i <= the negative part
// We can do check this for each prefix in constant time by holding a counter for each so in total it will take
// O(N) time

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
        int numDecr = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (i > 0 && a[i] <= a[i - 1]) numDecr++;
        }

        int oper = numDecr;
        int numIncr = 0;

        for (int i = 0; i < N; i++) {
            if (i > 0 && a[i - 1] <= a[i]) numIncr++;
            if (i < N - 1 && a[i] >= a[i + 1]) numDecr--;
            oper = min(oper, numIncr + numDecr + 1);
        }

        cout << oper << endl;
    }
}