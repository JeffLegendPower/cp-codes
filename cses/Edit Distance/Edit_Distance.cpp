// https://cses.fi/problemset/task/1639

// To solve this using dp, we need to imagine that we have 2 words that are both
// the same. Now, either a letter can be added to the first word, a letter can be added to the
// second word, or a letter can be added to both words. If a letter is added to one of the words, then the distance between them
// increases by 1. If a letter is added to both words, then the distance increases by 1 if and only if the 2 letters are different
// We can use this information to solve this problem with DP in O(n*m), as we will have a 2d array, where i,j represents
// string n up to the ith letter and string m up to the jth letter. We can then think of the steps stated above as
// transitions, as once we calculate the edit distance for i,j, we can act like that we fixed the strings to be equal to eachother
// So then transitioning from that point to i+1,j, i,j+1, or i+1,j+1 is as simple as the observation above

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
    string n, m;
    cin >> n >> m;

    int N = n.size(), M = m.size();

    ll editdist[N + 1][M + 1];
    editdist[0][0] = 0;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            if (i == 0 && j == 0) continue;
            ll mindist = 1e18;
            if (i > 0 && j > 0) mindist = min(mindist, editdist[i - 1][j - 1] + (n[i - 1] != m[j - 1]));
            if (i > 0) mindist = min(mindist, editdist[i - 1][j] + 1);
            if (j > 0) mindist = min(mindist, editdist[i][j - 1] + 1);

            editdist[i][j] = mindist;
        }
    }

    cout << editdist[N][M];
}