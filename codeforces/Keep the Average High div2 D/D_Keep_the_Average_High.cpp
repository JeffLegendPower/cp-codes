// https://codeforces.com/contest/1616/problem/D

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
ll t[2 * Nmax];

ll oper(ll a, ll b) {
    return min(a, b);
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 1e18;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> N;

        ll a[N];
        for (int i = 0; i < N; i++) cin >> a[i];
        ll x;
        cin >> x;

        for (int i = 0; i < N; i++) a[i] -= x;

        ll pres[N + 1];
        pres[0] = 0;
        for (int i = 0; i < N; i++) {
            pres[i + 1] = pres[i] + a[i];
            t[N + i] = pres[i + 1];
        }
        build();

        vector<int> minidx(N, -1);
        for (int i = 0; i < N - 1; i++) {
            // Find first less than target
            ll target = pres[i];
            int low = i + 1, high = N - 1;
            int best = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                // cout << mid << endl;
                ll least = query(i + 1, mid + 1);
                // cout << least << endl;

                if (least >= target) low = mid + 1;
                else {
                    high = mid - 1;
                    best = mid;
                }
            }
            
            minidx[i] = best;
            // cout << i << " " << target << " " << minidx[i] << endl;
        }
        int selected = N;
        pii range = {-1, -1};

        for (int i = 0; i < N; i++) {
            if (minidx[i] == -1) continue;

            pii currange = {i, minidx[i]};
            if (currange.first > range.second) {
                selected--;
                range = currange;
            } else {
                range.first = max(range.first, currange.first);
                range.second = min(range.second, currange.second);
            }
        }

        cout << selected << endl;
    }
}