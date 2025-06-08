// Problem link here:

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
        int N, Q;
        cin >> N >> Q;

        string a, b;
        cin >> a >> b;

        int prea[N + 1][26], preb[N + 1][26];
        for (int i = 0; i < 26; i++) {
            prea[0][0] = 0;
            preb[0][0] = 0;
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 26; j++) {
                prea[i + 1][j] = prea[i][j];
                preb[i + 1][j] = preb[i][j];
            }

            prea[i + 1][a[i] - 'a']++;
            preb[i + 1][b[i] - 'a']++;
        }

        while (Q--) {
            int l, r;
            cin >> l >> r;

            int oper = 0;
            for (int i = 0; i < 26; i++) {
                oper += max(0, preb[r][i] - preb[l - 1][i] - prea[r][i] + prea[l - 1][i]);
            }

            cout << oper << endl;
        }
    }
}