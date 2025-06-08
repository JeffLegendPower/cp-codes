// https://cses.fi/problemset/task/1749

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
const int Nmax = 1e6;  // limit for array size
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
    if (l&1) res = res + t[l++];
    if (r&1) res = res + t[--r];
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N2;
    cin >> N2;

    N = 1<<(__lg(N2) + 1);

    ll x[N2];
    for (int i = 0; i < N2; i++) cin >> x[i];

    for (int j = 0; j < N2; j++) {
        int p;
        cin >> p;

        int rem = j;
        int best = 0;
        int low = 0, high = N;
        for (int i = 1; i < 2*N;) {
            if ((i<<1) >= 2*N) {
                best = i - N;
                break;
            }

            int rightlow = low + (high - low) / 2;

            if (rightlow >= N2) {
                i = i<<1;
                high = rightlow;
                continue;
            }

            int rightidx = rightlow - (rem - t[i<<1|1]);
            if (rightidx <= p - 1) {
                i = i<<1|1;
                low = rightlow;
            } else {
                rem -= t[i<<1|1];
                i = i<<1;
                high = rightlow;
            }
        }
        modify(best, 1);

        cout << x[best] << " ";
    }
}