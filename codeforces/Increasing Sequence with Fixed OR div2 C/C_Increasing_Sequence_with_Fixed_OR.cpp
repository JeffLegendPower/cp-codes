// Problem link here:

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
        ll N;
        cin >> N;

        int sigbit = 0;
        for (int i = 0; i < 60; i++) {
            if ((N & (1ll << i)) > 0) sigbit = i;
        }

        vector<ll> nums;
        // nums.push_back(((1ll << sigbit) - 1) & N);
        // nums.push_back(1ll << sigbit);
        nums.push_back(N);
        for (int i = 0; i < 60; i++) {
            if ((N & (1ll << i)) > 0) {
                ll next = N ^ (1ll << i);
                if (next > 0) nums.push_back(next);
            }
        }

        cout << nums.size() << endl;
        for (int i = nums.size() - 1; i >= 0; i--) cout << nums[i] << " ";
        cout << endl;
    }
}