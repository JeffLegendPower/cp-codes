// https://codeforces.com/contest/2005/problem/B1

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

    while (T--) {
        ll N;
        int M, Q;
        cin >> N >> M >> Q;

        set<ll> teach1;
        set<ll, greater<ll>> teach2;
        for (int i = 0; i < M; i++) {
            ll teach;
            cin >> teach;
            teach1.insert(teach);
            teach2.insert(teach);
        }

        while (Q--) {
            ll a;
            cin >> a;

            if (teach1.lower_bound(a) != teach1.end() && *teach1.lower_bound(a) == a) {
                cout << 0 << endl;
                continue;
            }

            auto high = teach1.upper_bound(a), low = teach2.upper_bound(a);
            if (high == teach1.end()) {
                cout << (N - *low) << endl;
                continue;
            } if (low == teach2.end()) {
                cout << (*high - 1) << endl;
                continue;
            }

            ll low1 = *low;
            ll high1 = *high;

            ll mid = low1 + (high1 - low1) / 2;

            cout << min(high1 - mid, mid - low1) << endl;
        }
    }
}