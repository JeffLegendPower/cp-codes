// https://codeforces.com/contest/1995/problem/D

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
        int N, k;
        int c;
        cin >> N >> c >> k;

        string s;
        cin >> s;

        vector<bool> badsets;
        for (int i = 0; i < (1 << c); i++) badsets.push_back(false);

        // Good must contain last letter in the sequence, so any subset without this letter
        // must be bad
        badsets[((1 << c) - 1) ^ (1 << (s[N - 1] - 'A'))] = true;

        int count[c];
        for (int i = 0; i < c; i++) count[i] = 0;

        int badmask = 0;
        for (int i = 0; i < k; i++) {
            count[s[i] - 'A']++;
        }

        for (int i = 0; i < c; i++) {
            if (!count[i]) badmask |= 1<<i;
        }

        badsets[badmask] = true;
        for (int i = k; i < N; i++) {
            count[s[i - k] - 'A']--;
            count[s[i] - 'A']++;

            badmask = 0;
            for (int j = 0; j < c; j++) if (!count[j]) badmask |= 1<<j;

            badsets[badmask] = true;
        }

        int minsize = 1e6;

        for (int j = c; j >= 0; j--) {
            for (int msk = 0; msk < (1 << c); msk++) {
                if (__builtin_popcount(msk) != j) continue;

                if (!badsets[msk]) {
                    minsize = min(minsize, j);
                    continue;
                }

                for (int rem = 0; rem < c; rem++) {
                    int prev = msk ^ (1<<rem);
                    if (prev > msk) continue;

                    badsets[prev] = true;
                }
            }
        }

        cout << minsize << endl;
    }
}