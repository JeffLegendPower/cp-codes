// https://codeforces.com/contest/1983/problem/B

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

        int a[N][M];
        int b[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c;
                cin >> c;
                a[i][j] = c - '0';
            }
        } 
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c;
                cin >> c;
                b[i][j] = c - '0';
            }
        } 
        
        bool works = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (a[i][j] == b[i][j]) continue;
                if (i == N - 1 || j == M - 1) {
                    works = false;
                    goto end;
                }

                if ((a[i][j] + 1) % 3 == b[i][j]) {
                    a[i][j] = (a[i][j] + 1) % 3;
                    a[i + 1][j + 1] = (a[i + 1][j + 1] + 1) % 3;
                    a[i + 1][j] = (a[i + 1][j] + 2) % 3;
                    a[i][j + 1] = (a[i][j + 1] + 2) % 3;
                } else {
                    a[i][j] = (a[i][j] + 2) % 3;
                    a[i + 1][j + 1] = (a[i + 1][j + 1] + 2) % 3;
                    a[i + 1][j] = (a[i + 1][j] + 1) % 3;
                    a[i][j + 1] = (a[i][j + 1] + 1) % 3;
                }
            }
        }

        end:
        cout << (works ? "YES" : "NO") << endl;
    }
}