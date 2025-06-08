// https://codeforces.com/contest/1555/problem/E

// I can solve this using segtree and two pointers
// First, I'll need to sort the ranges in increasing order
// based on their weights
// Note that because the cost is defined as max weight - min weight, if I have picked
// a range with the max and a range with the min weights, it will never hurt, only help, to include
// all the ranges with weights inbetween these values (inclusive)
// Now I can use two pointers to find the minimum cost
// First I'll set the left bound to 0 and right to N - 1
// Then I'll keep decreasing the right bound as much as possible until
// I can't have a smaller good subset
// Finally, since I may have removed a more "essential" range which adding back could allow me to remove more ranges
// on the lower side
// I'll increment the left side until N - 1, and each time I will increment the right side as much as possible
// I'll track the minimum cost the whole time and print that once all this is done

// Now, adding or removing a range and updating my subset would take O(M) time as I would need to go through
// all M points
// HOWEVER... this is where segtree comes in
// Each leaf node will describe the number of ranges on that point
// I can add/remove ranges in O(logM) using lazy updates with segtree
// And query the entire segtree for the minimum of all the leaf nodes
// If the minimum > 0, then we have a valid union

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
typedef pair<int, int> pii;

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

int h = sizeof(int) * 8 - __builtin_clz(N);
int d[Nmax];  

void apply(int p, int value) {
  t[p] += value;
  if (p < N) d[p] += value;
}

void build(int p) {
  while (p > 1) p >>= 1, t[p] = min(t[p<<1], t[p<<1|1]) + d[p];
}

void push(int p) {
  for (int s = h; s > 0; --s) {
    int i = p >> s;
    if (d[i] != 0) {
      apply(i<<1, d[i]);
      apply(i<<1|1, d[i]);
      d[i] = 0;
    }
  }
}

void inc(int l, int r, int value) {
  l += N, r += N;
  int l0 = l, r0 = r;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) apply(l++, value);
    if (r&1) apply(--r, value);
  }
  build(l0);
  build(r0 - 1);
}

int query(int l, int r) {
  l += N, r += N;
  push(l);
  push(r - 1);
  int res = 1e6;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(t[--r], res);
  }
  return res;
}
// Segtree end

struct rnge {
    int l, r, w;
};

int main() {
    int n, M;
    cin >> n >> M;
    N = M - 1;

    rnge ranges[n];
    for (int i = 0; i < n; i++) cin >> ranges[i].l >> ranges[i].r >> ranges[i].w;
    sort(ranges, ranges + n, [](rnge one, rnge two) {
        return one.w < two.w;
    });

    for (int i = 0; i < Nmax; i++) {
        d[i] = 0;
        t[2 * i] = 0;
        t[2 * i + 1] = 0;
    }

    for (int i = 0; i < n; i++) {
        inc(ranges[i].l - 1, ranges[i].r - 1, 1);
        // cout << query(0, N) << endl;
    } // 0 4, 2 3, 3 9, 10 11, 9 11

    int mincost = ranges[n - 1].w - ranges[0].w;
    int left = n - 1;
    while (left > 0) {
        inc(ranges[left].l - 1, ranges[left].r - 1, -1);
        int res = query(0, N);
        if (res > 0) {
            mincost = min(mincost, ranges[left - 1].w - ranges[0].w);
        } else {
            // cout << left << endl;
            inc(ranges[left].l - 1, ranges[left].r - 1, 1);
            break;
        }
        left--;
    }

    int right = 0;
    while (left < n) {
        while (right < left) {
            inc(ranges[right].l - 1, ranges[right].r - 1, -1);
            int res = query(0, N);
            if (res > 0) {
                mincost = min(mincost, ranges[left].w - ranges[right + 1].w);
                // if (mincost == 0) cout << right << " " << left << endl;
            } else {
                inc(ranges[right].l - 1, ranges[right].r - 1, 1);
                break;
            }
            right++;
        }

        left++;
        if (left < n)
            inc(ranges[left].l - 1, ranges[left].r - 1, 1);
    }

    cout << mincost << endl;
}