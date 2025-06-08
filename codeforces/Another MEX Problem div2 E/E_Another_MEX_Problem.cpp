// https://codeforces.com/contest/1870/problem/E

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

        int a[N];
        int mexs[N] = {-1};
        int mexidxs[N + 1] = {-1};

        for (int i = 0; i < N; i++) mexs[i] = -1;
        for (int i = 0; i <= N; i++) mexidxs[i] = -1;
        
        for (int i = 0; i < N; i++) cin >> a[i];


        bool xors[N][1<<13];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 1<<13; j++) xors[i][j] = false;
        }

        if (a[0] == 0) {
            xors[0][1] = true;
            mexs[0] = 1;
            mexidxs[1] = 0;
        } else {
            xors[0][0] = true;
            mexs[0] = 0;
            mexidxs[0] = 0;
        }

        for (int i = 1; i < N; i++) {
            for (int j = 0; j < 1<<13; j++) xors[i][j] |= xors[i - 1][j];
            
            if (a[i] == 0) {
                for (int j = 0; j < 1<<13; j++) xors[i][j ^ 1] |= xors[i - 1][j];
                mexidxs[1] = i;
                mexs[i] = 1;
            } else {
                mexidxs[0] = i;
                mexs[i] = 0;
            }


            int target = mexidxs[a[i]];
            int mex = 0;
            bool has[N + 1] = {false};

            if (target == -1) continue;

            for (int j = i; j >= target; j--) {
                has[a[j]] = true;
                while (has[mex]) mex++;
            }

            for (int j = 0; j < 1<<13; j++) if (target > 0) xors[i][j ^ mex] |= xors[target - 1][j];

            xors[i][mex] = true;
            mexidxs[mex] = max(mexidxs[mex], target);
            mexs[target] = mex;

            target--;

            int lastmex = mex, curmex = mex;
            while (target >= 0 && mexs[target] < mex) {
                has[a[target]] = true;
                while (has[curmex]) curmex++;

                mexidxs[curmex] = max(mexidxs[curmex], target);
                mexs[target] = curmex;

                if (lastmex == curmex) {
                    target--;
                    continue;
                }
                lastmex = curmex;

                for (int j = 0; j < 1<<13; j++) if (target > 0) xors[i][j ^ curmex] |= xors[target - 1][j];
                xors[i][curmex] = true;
                target--;
            }

            mexs[target] = mex;
        }

        int best = 0;
        for (int i = 0; i < 1<<13; i++) if (xors[N - 1][i]) best = i;

        cout << best << endl;
    }
}