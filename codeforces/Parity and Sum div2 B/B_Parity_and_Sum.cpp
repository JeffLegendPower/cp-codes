// https://codeforces.com/contest/1993/problem/B

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
        int N;
        cin >> N;

        vector<ll> evens;

        ll maxodd = -1;
        for (int i = 0; i < N; i++) {
            ll a;
            cin >> a;

            if (a % 2 == 1) maxodd = max(maxodd, a);
            else evens.push_back(a);
        }

        sort(evens.begin(), evens.end());

        if (evens.size() == N || evens.size() == 0) {
            cout << 0 << endl;
            continue;
        }

        ll maxeven = evens.back();
        if (maxodd > maxeven) {
            cout << evens.size() << endl;
            continue;
        }

        ll oper = 0;
        for (ll even : evens) {
            if (maxodd > even) {
                oper++;
                maxodd = even + maxodd;
                continue;
            }

            maxodd += maxeven;
            oper++;

            // ll numerator = even - maxodd;
            // ll n = numerator / maxeven;
            // if (numerator % maxeven > 0) n++;

            maxodd = even + maxodd;
            // oper += n;

            oper++;
        }

        cout << oper << endl;
    }
}