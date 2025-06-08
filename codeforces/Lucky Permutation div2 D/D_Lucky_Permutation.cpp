// https://codeforces.com/contest/1768/problem/D

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

        int p[N];
        int idx[N + 1];
        idx[0] = -1;
        int numdisorder = 0;
        for (int i = 0; i < N; i++) {
            cin >> p[i];
            idx[p[i]] = i;
            if (p[i] != i + 1) numdisorder++;
        }

        int minoper = 1e6;

        cout << numdisorder << endl;

        for (int i = 0; i < N - 1; i++) {
            int left = i + 2, right = i + 1;
            int leftidx = i, rightidx = i + 1;

            int oper = 0;

            if (p[leftidx] == right && p[rightidx] == left) {
                minoper = min(minoper, 1 + max(0, numdisorder - 1));
                continue;
            } else if (p[leftidx] == left && p[rightidx] == right) {
                // minoper = min(minoper, numdisorder)
            }

            // int localdisorder = numdisorder;

            // if (p[leftidx] != left) {
            //     int fromidx = idx[left];
            //     if (p[leftidx] == fromidx + 1) localdisorder--;
            // }
        }
        cout << minoper << endl;
    }
}