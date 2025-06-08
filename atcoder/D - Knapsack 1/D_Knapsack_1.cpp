// https://atcoder.jp/contests/dp/tasks/dp_d

// We can have an array of size W + 1 which stores the maximum value for each weight (default 0)
// We can then iterate through all N items and then for each item go through W and at each weight,
// add the weight of the ith item and add the value, and if value[weight] + v_i > value[weight + w_i]
// then set value[weight + w_i] to that
// Finally, we can store the maximum of the array and output that
// to get the maximum value

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
    int N, W;
    cin >> N >> W;

    ll val[W + 1];
    for (int i = 0; i <= W; i++) val[i] = 0;

    ll most = 0;
    for (int i = 0; i < N; i++) {
        int wi;
        ll vi;
        cin >> wi >> vi;

        for (int j = W - wi; j >= 0; j--) {
            val[j + wi] = max(val[j + wi], val[j] + vi);
            most = max(most, val[j + wi]);
        }
    }

    cout << most << endl;
}