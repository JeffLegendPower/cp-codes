// https://codeforces.com/contest/1801/problem/B

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
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        pll depts[N];
        for (int i = 0; i < N; i++) cin >> depts[i].first >> depts[i].second;

        sort(depts, depts + N);

        set<ll> available;
        set<ll, greater<ll>> available2;

        ll bmaxsuff[N];
        bmaxsuff[N - 1] = -1e9;
        for (int i = N - 2; i >= 0; i--) {
            bmaxsuff[i] = max(bmaxsuff[i + 1], depts[i + 1].second);
        }

        ll mindiff = 1e18;

        for (int i = 0; i < N; i++) {

            ll a = depts[i].first;
            ll b = bmaxsuff[i];

            ll b2 = -1e18;
            ll b3 = -1e18;

            auto itr1 = available.lower_bound(a);
            auto itr2 = available2.lower_bound(a);
            if (itr1 != available.end()) {
                b2 = *itr1;
            } if (itr2 != available2.end()) {
                b3 = *itr2;
            }

            if (abs(a - b3) < abs(a - b)) b = max(b, b3);
            if (abs(a - b2) < abs(a - b)) b = max(b, b2);

            mindiff = min(mindiff, abs(a - b));

            // at end
            available.insert(depts[i].second);
            available2.insert(depts[i].second);
        }

        cout << mindiff << endl;
    }
}