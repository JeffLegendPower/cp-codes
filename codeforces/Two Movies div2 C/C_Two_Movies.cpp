// https://codeforces.com/contest/1989/problem/C

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

        int a[N], b[N];
        for (int i = 0; i < N; i++) cin >> a[i];
        for (int i = 0; i < N; i++) cin >> b[i];

        pii ratings = {0, 0};
        int pos = 0, neg = 0;

        for (int i = 0; i < N; i++) {
            if (a[i] > b[i]) ratings.first += a[i];
            else if (b[i] > a[i]) ratings.second += b[i];
            else {
              if (a[i] == 0) continue;
              if (a[i] == 1) pos++;
              else neg++;
            }
        }

        // cout << ratings.first << " " << ratings.second << " " << pos << " " << neg << endl;
        if (pos == 0) {
          cout << min(ratings.first, ratings.second) << endl;
          continue;
        }

        if (pos > 0) {
          int diff = max(ratings.first, ratings.second) - min(ratings.first, ratings.second);
          if (pos <= diff) {
            cout << min(ratings.first, ratings.second) + pos << endl;
            continue;
          }
          pos -= diff;
          cout << max(ratings.first, ratings.second) + pos / 2 << endl;
        } else {
          int diff = max(ratings.first, ratings.second) - min(ratings.first, ratings.second);
          if (abs(pos) <= diff) {
            cout << max(ratings.first, ratings.second) + pos << endl;
            continue;
          }
          pos += diff;
          cout << min(ratings.first, ratings.second) + (pos - 1) / 2 << endl;
        }
    }
}