// https://codeforces.com/contest/1744/problem/F

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define int long long
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


signed main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        int p[N];
        int idxs[N];
        for (int i = 0; i < N; i++) {
            cin >> p[i];
            idxs[p[i]] = i;
        }

        ll total = 0;
        int leftmex = 0, rightmex = 0;
        vector<bool> leftnums(N, false), rightnums(N, false);
        int leftidx = -1, rightidx = N;

        int l = idxs[0], r = idxs[0];

        for (int mex = 1; mex <= N; mex++) {
            if (l > idxs[mex - 1]) {
                l = idxs[mex - 1];
            } else if (r < idxs[mex - 1]) {
                r = idxs[mex - 1];
            }

            if (mex < N && l <= idxs[mex] && idxs[mex] <= r) continue;

            int maxlen = 2 * mex;

            int lowerl = 0;
            if (mex < N && idxs[mex] < l) lowerl = idxs[mex] + 1;
            int maxr = N - 1;
            // cout << l << endl;
            if (mex < N && idxs[mex] > r) maxr = idxs[mex] - 1;

            int start = max(r - maxlen + 1, lowerl);
            int end = l;

            if (end >= start) {
                int cnt = end - start + 1;

                int first = min(maxr, maxlen + start - 1) - r + 1;
                int last = min(maxr, maxlen + end - 1) - r + 1;

                total += cnt * (first + last) / 2;
            }
        }

        cout << total << endl;
    }
}