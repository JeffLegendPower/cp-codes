// https://codeforces.com/contest/1980/problem/F1

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
        ll N, M;
        int k;
        cin >> N >> M >> k;

        // fountsup: when alice part is top, fountsdown, when alice part is bottom
        pll fountsup[k], fountsdown[k];
        for (int i = 0; i < k; i++) {
            cin >> fountsup[i].first >> fountsup[i].second;
            fountsdown[i] = fountsup[i];
        }

        sort(fountsup, fountsup + k, [](pll one, pll two) {
            if (one.second == two.second) return one.first < two.first;
            return one.second < two.second;
        }); sort(fountsdown, fountsdown + k, [](pll one, pll two) {
            if (one.second == two.second) return one.first > two.first;
            return one.second < two.second;
        });

        vector<pll> fountsupsuff, fountsdownsuff;
        fountsupsuff.push_back(fountsup[k - 1]);
        for (int i = k - 2; i >= 0; i--) {
            fountsupsuff.push_back({max(fountsupsuff.back().first, fountsup[i].first), fountsup[i].second});
        }
        reverse(fountsupsuff.begin(), fountsupsuff.end());
        for (int i = 0; i < k; i++) cout << fountsupsuff[i].first << " " << fountsupsuff[i].second << endl;
    }
}