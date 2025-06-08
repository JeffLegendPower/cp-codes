// https://codeforces.com/contest/1299/problem/A

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

    int N;
    cin >> N;

    ll a[N];
    vector<ll> bitcnts(32, 0);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        for (int bit = 0; bit < 32; bit++) if (a[i] & (1ll<<bit)) bitcnts[bit]++;
    }

    ll best = -1;
    ll bestfirst = 0;
    for (int i = 0; i < N; i++) {
        ll score = 0;
        for (int bit = 0; bit < 32; bit++) {
            ll cnt = bitcnts[bit];
            if (a[i] & (1ll<<bit)) cnt--;
            if (cnt == 0) score |= 1ll<<bit;
        }

        if (score > best) {
            bestfirst = a[i];
            best = score;
        }
    }

    bool found = false;
    int idx = 1;

    cout << bestfirst << " ";
    for (int i = 0; i < N; i++) {
        if (a[i] == bestfirst && !found) {
            found = true;
            continue;
        }
        cout << a[i] << " ";
    }
}