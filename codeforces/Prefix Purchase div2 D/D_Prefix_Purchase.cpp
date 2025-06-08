// https://codeforces.com/contest/1870/problem/D

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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    int T2 = T;
    ll sumN = 0;

    while (T--) {
        int N;
        cin >> N;

        sumN += N;

        ll c[N];
        for (int i = 0; i < N; i++) cin >> c[i];
        ll k;
        cin >> k;

        ll minc[N];
        minc[N - 1] = c[N - 1];
        for (int i = N - 2; i >= 0; i--) minc[i] = min(minc[i + 1], c[i]);

        ll a[N] = {0ll};
        a[0] = k / minc[0];

        ll cost = a[0] * minc[0];

        for (int i = 1; i < N; i++) {
            if (minc[i] == minc[i - 1]) {
                a[i] = a[i - 1];
                continue;
            }

            ll low = 0, high = a[i - 1];
            ll best = 0;
            while (low <= high) {
                ll mid = low + (high - low) / 2;

                ll cost2 = cost + mid * minc[i] - mid * minc[i - 1];
                if (cost2 <= k) {
                    low = mid + 1;
                    best = mid;
                } else high = mid - 1;
            }

            cost = cost + best * minc[i] - best * minc[i - 1];
            a[i] = best;
        }

        for (int i = 0; i < N; i++) cout << a[i] << " ";
        cout << endl;
    }
}