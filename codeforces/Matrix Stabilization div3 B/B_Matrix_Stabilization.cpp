// https://codeforces.com/contest/1986/problem/B

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        ll a[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) cin >> a[i][j];
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ll target = 0;
                if (i > 0)
                    target = max(target, a[i - 1][j]);
                if (i < N - 1)
                    target = max(target, a[i + 1][j]);
                if (j > 0)
                    target = max(target, a[i][j - 1]);
                if (j < M - 1)
                    target = max(target, a[i][j + 1]);
                
                a[i][j] = min(a[i][j], target);

                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }
}