// https://codeforces.com/contest/1375/problem/D

// Let's try to get an array where a[i] = i ([0, 1, 2, .., N - 2, N - 1])
// We will have fixed (where a[i] = i) and unfixed (where a[i] /= i) points
// If mex(a) == N, we don't want that so we will set any unfixed point to the mex
// Otherwise, mex(a) will be equal to some value which isn't in the array, so it can't be at a[mex]
// By setting a[mex] to mex, we are adding another fixed point. We will keep doing this until every
// point is fixed and our array a looks like [0, 1, 2, ..., N - 2, N - 1]

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

        int a[N];
        int freq[N + 1];
        for (int i = 0; i <= N; i++) freq[i] = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }

        vector<int> oper;

        while (true) {
            int mex = 0;
            while (freq[mex] > 0) mex++;

            if (mex == N) {
                bool found = false;
                for (int i = 0; i < N; i++) {
                    if (a[i] == i) continue;
                    freq[a[i]]--;
                    freq[mex]++;
                    a[i] = mex;
                    oper.push_back(i + 1);
                    found = true;
                    break;
                }
                if (!found) break;
            } else {
                freq[a[mex]]--;
                freq[mex]++;
                a[mex] = mex;
                oper.push_back(mex + 1);
            }
        }

        cout << oper.size() << endl;
        for (int i = 0; i < oper.size(); i++) cout << oper[i] << " ";
        cout << endl;
    }
}