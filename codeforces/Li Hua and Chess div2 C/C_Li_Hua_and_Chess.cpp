// https://codeforces.com/contest/1797/problem/C

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

ll dist(pll one, pll two) {
    return max(one.first - two.first, one.second - two.second);
}

int main() {
    // Comment out for interactive problems
    // ios::sync_with_stdio(false);
	// cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll N, M;
        cin >> N >> M;

        cout << "? 1 1" << endl;
        ll ans1;
        cin >> ans1;
        cout << "? " << N << " " << M << endl;
        ll ans2;
        cin >> ans2;

        if (N == 1) {
            cout << "! 1 " << (1 + ans1) << endl;
            continue;
        } if (M == 1) {
            cout << "! " << (1 + ans1) << " " << 1 << endl;
            continue;
        }

        pll coord1 = {min(N, ans1 + 1), max(1ll, M - ans2)};
        pll coord2 = {max(1ll, N - ans2), min(M, ans1 + 1)};

        pll third = coord1;
        pll fourth = coord2;
        if (third.first < 1 || third.first > N || third.second < 1 || third.second > M) {
            third = coord2;
            fourth = coord1;
        }

        cout << "? " << third.first << " " << third.second << endl;
        ll ans3;
        cin >> ans3;
        
        if (ans3 == 0) {
            cout << "! " << third.first << " " << third.second << endl;
        } else
         cout << "! " << fourth.first << " " << fourth.second << endl;

        // if (dist(coord1, third) == ans3) {
        //     cout << "! " << coord1.first << " " << coord1.second << endl;
        // } else
        //  cout << "! " << coord2.first << " " << coord2.second << endl;
    }
}