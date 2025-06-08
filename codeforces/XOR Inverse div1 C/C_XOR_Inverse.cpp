// https://codeforces.com/contest/1416/problem/C

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

    vector<vector<ll>> splits[31];
    splits[30].push_back({});
    for (int i = 0; i < N; i++) {
        ll a;
        cin >> a;
        splits[30][0].push_back(a);
    }

    ll x = 0;
    ll total = 0;
    for (int bit = 29; bit >= 0; bit--) {
        ll num1, num0;
        ll inversionunset = 0, inversionset = 0;
        for (vector<ll> split : splits[bit + 1]) {
            num1 = 0, num0 = 0;

            splits[bit].push_back({});
            splits[bit].push_back({});
            int endidx = splits[bit].size() - 1;

            for (ll ele : split) {
                if (ele & (1ll<<bit)) {
                    num1++;
                    inversionset += num0;
                    splits[bit][endidx - 1].push_back(ele);
                } else {
                    num0++;
                    inversionunset += num1;
                    splits[bit][endidx].push_back(ele);
                }
            }

            if (splits[bit][endidx].empty()) splits[bit].erase(splits[bit].begin() + endidx);
            if (splits[bit][endidx - 1].empty()) splits[bit].erase(splits[bit].begin() + endidx - 1);
        }

        if (inversionset < inversionunset) {
            x |= 1ll<<bit;
            for (int i = 0; i < splits[bit].size(); i++) {
                for (int j = 0; j < splits[bit][i].size(); j++) {
                    splits[bit][i][j] ^= 1ll<<bit;
                }
            }
        }

        total += min(inversionset, inversionunset);
    }

    cout << total << " " << x << endl;
}