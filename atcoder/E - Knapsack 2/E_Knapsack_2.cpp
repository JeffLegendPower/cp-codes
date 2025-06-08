// https://atcoder.jp/contests/dp/tasks/dp_e

// We can solve this by creating an array of size N * max(v) (which is at most 1e5)
// And for each value we find the minimum weight to achieve it
// We do this by iterating over each item and adding their value and taking the minimum of weight[value + v_i] and weight[value] + w_i

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


// Segtree start
const int Nmax = 1e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


int main() {
    int N;
    ll W;
    cin >> N >> W;

    ll weights[100000 + 1];
    weights[0] = 0;
    for (int i = 1; i <= 1e5; i++) {
        weights[i] = 1e15;
    }

    int most = 0;

    for (int i = 0; i < N; i++) {
        ll wi;
        int vi;
        cin >> wi >> vi;

        for (int j = 1e5 - vi; j >= 0; j--) {
            weights[j + vi] = min(weights[j + vi], weights[j] + wi);
            if (weights[j + vi] <= W) most = max(most, j + vi);
        }
    }

    cout << most << endl;
}