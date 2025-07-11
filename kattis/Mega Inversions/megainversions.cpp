// https://open.kattis.com/problems/megainversions

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 1e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

ll oper(ll a, ll b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // add value at position p
  for (t[p += N] += value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 0;
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

    cin >> N;

    ll a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    ordered_multiset oset;

    ll doubles[N];

    for (int i = N - 1; i >= 0; i--) {
        doubles[i] = oset.order_of_key({a[i], 0});

        oset.insert({a[i], i});
    }

    ordered_multiset oset2;
    ll triples = 0;
    for (int i = N - 1; i >= 0; i--) {
        // need to do -1 because otherwise if a[i] == N it will go past the segtree bounds and break stuff
        triples += query(0, a[i] - 1);

        modify(a[i] - 1, doubles[i]);
    }

    cout << triples;
}