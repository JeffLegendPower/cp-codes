// https://codeforces.com/contest/1832/problem/D1

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

    ll N, Q;
    cin >> N >> Q;

    ll a[N];
    for (int i = 0; i < N; i++) cin >> a[i];
    sort(a, a + N);

    while (Q--) {
        ll k;
        cin >> k;

        if (k <= N) {
            ll least = 1e18;
            for (ll i = 0; i < k; i++) {
                least = min(least, a[i] + k - i);
            } for (ll i = k; i < N; i++) least = min(least, a[i]);
            cout << least << " ";
            continue;
        }

        bool notlast = false;
        if ((k - N) % 2 == 1) notlast = true;
        
        ll low = -1e18, high = 1e18;
        ll best = 0;
        while (low <= high) {
            ll mid = low + (high - low) / 2;

            ll numrem = (k - N + 1) / 2;

            ll add = k;
            ll least = 1e18;
            for (int i = 0; i < N - notlast; i++) {
                ll cur = a[i] + add;
                ll rem = min(max(cur - mid, 0ll), numrem);
                numrem -= rem;
                cur -= rem;

                least = min(least, cur);
                add--;
            }

            if (notlast) {
                ll rem = min(max(a[N - 1] - mid, 0ll), numrem);
                numrem -= rem;
                least = min(least, a[N - 1] - rem);
            }

            if (least < mid || numrem > 0) {
                high = mid - 1;
            } else {
                low = mid + 1;
                best = mid;
            }
        }

        cout << best << " ";
    }
}