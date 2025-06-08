// https://cses.fi/problemset/task/1145

// Naively we could solve this in O(2^n) by testing every subset of elements
// But we can solve this in O(n^2) dp by having a dp array storing the
// mininimum last element that can achieve an LIS of length i
// We will initialize lis[0] = 0, and lis[i] = inf for all 1 <= i <= N
// Then, for each element we can iterate through the lis, if lis[i] < x[i], then
// lis[i + 1] = min(lis[i + 1], x[i]). And we can keep a variable to remember the longest
// LIS we achieved. However, n <= 1e5, so O(n^2) doesn't work. However, we can use binary search
// when updating the lis for each element to run our algorithm in O(nlogn)
// This is possible because we are only needing to change the lis array at most once for each element
// as lis[i] < lis[j] for all i < j. And since the lis array is in increasing order, we can use binary search
// to find the largest element smaller than x[i] and update the lis at only that point

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

    // Minimum last value that can achieve an LIS of length i
    // This will always be in increasing order so we can binary search it
    ll lis[N + 1];
    lis[0] = 0;
    int maxlis = 0;
    for (int i = 1; i <= N; i++) lis[i] = 1e18;
    for (int i = 0; i < N; i++) {
        ll x;
        cin >> x;

        int low = 0, high = N - 1;
        int best = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (lis[mid] < x) {
                low = mid + 1;
                best = mid;
            } else high = mid - 1;
        }

        lis[best + 1] = min(lis[best + 1], x);
        maxlis = max(maxlis, best + 1);
    }

    cout << maxlis;
}