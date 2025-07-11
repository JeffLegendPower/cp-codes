// https://cses.fi/problemset/task/1144

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

typedef tree<plli, null_type, less<plli>, rb_tree_tag, tree_order_statistics_node_update> oset;


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

    int N, Q;
    cin >> N >> Q;

    oset ost;

    ll salaries[N];
    for (int i = 1; i <= N; i++) {
        ll p;
        cin >> p;
        salaries[i - 1] = p;
        ost.insert({p, i});
    }

    while (Q--) {
        char c;
        cin >> c;

        if (c == '!') {
            int k;
            ll x;
            cin >> k >> x;

            ost.erase({salaries[k - 1], k});
            
            ost.insert({x, k});
            salaries[k - 1] = x;
        } else if (c == '?') {
            ll a, b;
            cin >> a >> b;

            cout << ost.order_of_key({b, 2e5 + 1}) - ost.order_of_key({a - 1, 2e5 + 1}) << endl;
        }
    }
}