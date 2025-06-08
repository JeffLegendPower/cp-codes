// https://codeforces.com/contest/1689/problem/D

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

        char grid[N][M];
        int upmost[M];
        int downmost[M];
        for (int i = 0; i < M; i++) {
            upmost[i] = 1e7;
            downmost[i] = -1;
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'B') {
                    upmost[j] = min(upmost[j], i);
                    downmost[j] = max(downmost[j], i);
                }
            }
        }

        int besta = -1, bestb = -1;
        int bestdist = 1e7;
        for (int i = 0; i < N; i++) {
            int rightdist = -1;
            int leftdist = -1;
            for (int j = 0; j < M; j++) {
                if (upmost[j] != 1e7) rightdist = max(rightdist, j + abs(upmost[j] - i));
                if (downmost[j] != -1) rightdist = max(rightdist, j + abs(downmost[j] - i));
            } for (int j = 0; j < M; j++) {
                if (upmost[j] != 1e7) leftdist = max(leftdist, abs(upmost[j] - i));
                if (downmost[j] != -1) leftdist = max(leftdist, abs(downmost[j] - i));

                int dist = max(rightdist, leftdist);
                if (dist < bestdist) {
                    bestdist = dist;
                    besta = i + 1;
                    bestb = j + 1;
                }

                if (leftdist != -1)
                    leftdist++;
                rightdist--;
            }
        }

        cout << besta << " " << bestb << endl;
    }
}