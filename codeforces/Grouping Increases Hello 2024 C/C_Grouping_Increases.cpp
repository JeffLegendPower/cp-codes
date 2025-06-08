// https://codeforces.com/contest/1919/problem/C

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

        int a[N];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
        }

        vector<int> s, t;

        s.push_back(a[0]);
        t.push_back(1e6); // Some arbitrarily large number that won't be increasing considering the bounds
        for (int i = 1; i < N; i++) {
            if (a[i] <= s.back()) {
                if (a[i] <= t.back() && t.back() < s.back()) {
                    t.push_back(a[i]);
                } else s.push_back(a[i]);
            } else {
                if (a[i] <= t.back()) t.push_back(a[i]);
                else {
                    if (t.back() < s.back()) t.push_back(a[i]);
                    else s.push_back(a[i]);
                }
            }
        }

        int num = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] > s[i - 1]) num++;
        } for (int i = 1; i < t.size(); i++) {
            if (t[i] > t[i - 1]) num++;
        }

        cout << num << endl;
    }
}