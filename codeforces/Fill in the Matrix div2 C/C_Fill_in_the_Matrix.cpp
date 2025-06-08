// https://codeforces.com/contest/1869/problem/C

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
        int N, M;
        cin >> N >> M;

        if (M == 1) {
            cout << 0 << endl;
            for (int i = 0; i < N; i++) cout << 0 << endl;
            continue;
        } if (N == 1) {
            cout << 2 << endl;
            for (int i = 0; i < M; i++) cout << i << " ";
            cout << endl;
            continue;
        }

        int num = min(N + 1, M);

        int a[N][M];
        int i = 0;
        for (; i < num - 1; i++) {
            int start = i;
            for (int j = 0; j < M; j++) {
                int newj = (start + j) % M;
                a[i][newj] = j;
            }
        }

        for (; i < N; i++) {
            for (int j = 0; j < M; j++) a[i][j] = j;
        }

        cout << num << endl;
        for (i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) cout << a[i][j] << " ";
            cout << endl;
        }
    }
}