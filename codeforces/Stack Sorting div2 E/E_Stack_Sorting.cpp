// https://codeforces.com/contest/911/problem/E

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
const int Nmax = 1e6;  // limit for array size
int N;  // array size
int t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(res, t[--r]);
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int k;
    cin >> N >> k;
    
    int p[N];
    int numidxs[N + 1];

    for (int i = 0; i < N; i++) {
        t[N + i] = 0;
        numidxs[i + 1] = -1;
    }

    for (int i = 0; i < k; i++) {
        cin >> p[i];
        numidxs[p[i]] = i;

        t[N + i] = p[i];
    }

    build();

    int num = 1;
    int blankidx = k;

    while (num < N) {
        int idx = numidxs[num];
        int nextidx = numidxs[num + 1];

        if (idx == -1) {
            int next = num;
            int last = num;
            while (numidxs[last] == -1) last++;
            last--;

            num = last + 1;

            while (last >= next) {
                modify(blankidx, last);
                numidxs[last] = blankidx;
                p[blankidx++] = last--;
            }
        }

        if (nextidx != -1) {
            // int most = query(min(idx, nextidx), max(idx, nextidx) + 1);
            // if (most > num + 1) {
            //     possible = false;
            //     break;
            // }
            num++;
            continue;
        }

        int next = num + 1;
        int last = num + 1;
        while (numidxs[last] == -1) last++;
        last--;

        num = last + 1;

        while (last >= next) {
            modify(blankidx, last);
            numidxs[last] = blankidx;
            p[blankidx++] = last--;
        }
    }

    bool possible = true;
    for (int i = 1; i < N; i++) {
        if (numidxs[i + 1] > numidxs[i]) continue;
        int most = query(numidxs[i + 1], numidxs[i] + 1);
        if (most > i + 1) possible = false;
    }

    if (!possible) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 0; i < N; i++) cout << p[i] << " ";
}