// https://codeforces.com/contest/1797/problem/B

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
        ll k;
        cin >> N >> k;

        bool a1[N][N], a2[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> a1[i][j];
                a2[i][j] = a1[i][j];
            }
        }

        bool possible = true;
        ll rem = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int i2 = N - i - 1;
                int j2 = N - j - 1;
                if (a1[i][j] != a1[i2][j2]) {
                    rem++;
                    k--;
                    // cout << i << " " << j << "  " << i2 << " " << j2 << endl;
                    // cout << a1[i][j] << " " << a2[i2][j2] << endl;
                    a1[i2][j2] = a1[i][j];
                    // cout << a1[i][j] << " " << a2[i2][j2] << endl;
                }
            }
        }

        // k -= rem / 2;

        if (k < 0) possible = false;
        if ((N % 2 == 0) && (k % 2 == 1)) possible = false;

        cout << (possible ? "YES" : "NO") << endl;
    }
}