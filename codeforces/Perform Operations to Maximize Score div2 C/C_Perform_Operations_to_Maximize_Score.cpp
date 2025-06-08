// https://mirror.codeforces.com/contest/1998/problem/C

// #pragma GCC optimize ("trapv")

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

struct aa2 {
    ll val;
    int idx;
    ll b;
};

signed main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        ll k;
        cin >> N >> k;

        plli a[N];
        for (int i = 0; i < N; i++) cin >> a[i].first;
        for (int i = 0; i < N; i++) cin >> a[i].second;

        sort(a, a + N);

        ll score = a[N - 1].first + a[N / 2 - 1].first;

        for (int i = N - 1; i >= 0; i--) {
            if (a[i].second == 0) continue;
            if (i > floor(N / 2) - 1) score = max(score, a[i].first + k + a[N / 2 - 1].first);
            else score = max(score, a[i].first + k + a[N / 2].first);
        }

        ll low = 0, high = a[N - 1].first;
        while (low <= high) {
            int mid = low + (high - low) / 2;

            int needed = (N + 1) / 2;
            ll cost = 0;
            for (int i = N - 2; i >= 0; i--) {
                if (needed == 0) break;
                if (a[i].first >= mid) {
                    needed--;
                    continue;
                } if (a[i].second == 0) continue;
                cost += mid - a[i].first;
                needed--;
            }

            if (cost <= k && needed <= 0) {
                score = max(score, mid + a[N - 1].first);
                low = mid + 1;
            } else high = mid - 1;
        }

        cout << score << endl;
    }
}