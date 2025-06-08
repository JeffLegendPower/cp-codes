// https://codeforces.com/contest/1881/problem/G

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
struct node {
    ll first1 = -1, first2 = -1, last2 = -1, last1 = -1;
    bool ugly = false;
};

const int Nmax = 262144;  // limit for array size
int n;  // array size
node t[2 * Nmax];

ll d[Nmax];
int h;

node merge(node& left, node& right) {
    node cur;
    cur.ugly = left.ugly | right.ugly;

    if (left.last1 == right.first1) cur.ugly = true;
    if (left.last2 != -1 && left.last2 == right.first1) cur.ugly = true;
    if (right.first2 != -1 && left.last1 == right.first2) cur.ugly = true;

    cur.first1 = left.first1;
    cur.first2 = left.first2;
    if (cur.first2 == -1) cur.first2 = right.first1;
    cur.last1 = right.last1;
    cur.last2 = right.last2;
    if (cur.last2 == -1) cur.last2 = left.last1;

    return cur;
}
void update(node& cur, ll value) {
    if (cur.first1 != -1) cur.first1 = (cur.first1 + value) % 26;
    if (cur.first2 != -1) cur.first2 = (cur.first2 + value) % 26;
    if (cur.last1 != -1) cur.last1 = (cur.last1 + value) % 26;
    if (cur.last2 != -1) cur.last2 = (cur.last2 + value) % 26;
}

void apply(int p, ll value) {
    update(t[p], value);
    if (p < n) d[p] += value;
}

void build(int p) {
  while (p > 1) {
    p >>= 1;

    node left = t[p<<1], right = t[p<<1|1];
    t[p] = merge(left, right);
    update(t[p], d[p]);
  }
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

void modify(int l, int r, ll value) {
  l += n, r += n;
  int l0 = l, r0 = r;
  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) apply(l++, value);
    if (r&1) apply(--r, value);
  }
  build(l0);
  build(r0 - 1);
}

bool query(int l, int r) {
  l += n, r += n;
  push(l);
  push(r - 1);
  bool res = false;

  node left, right;

  for (; l < r; l >>= 1, r >>= 1) {
    if (l&1) {
        if (left.first1 == -1) left = t[l];
        else left = merge(left, t[l]);
        l++;
    } if (r&1) {
        r--;
        if (right.first1 == -1) right = t[r];
        else right = merge(t[r], right);
    }
  }

  return !merge(left, right).ugly;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        n = 1 << (__lg(N) + 1);
        h = sizeof(int) * 8 - __builtin_clz(n);

        string s;
        cin >> s;
        for (int i = 0; i < n; i++) {
            d[i] = 0;
            if (i < N) {
                t[n + i] = {s[i] - 'a', -1, -1, s[i] - 'a', false};
            } else t[n + i] = {-1, -1, -1, -1, false};
        }

        for (int i = 0; i < n; i++) build(n + i);

        while (M--) {
            int t;
            cin >> t;
            if (t == 1) {
                int l, r;
                ll x;
                cin >> l >> r >> x;

                modify(l - 1, r, x);
            } else {
                int l, r;
                cin >> l >> r;

                cout << (query(l - 1, r) ? "YES" : "NO") << endl;
            }
        }
    }
}