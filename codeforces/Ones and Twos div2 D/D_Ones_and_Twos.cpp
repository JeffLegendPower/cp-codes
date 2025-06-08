// https://codeforces.com/contest/1896/problem/D

// If we have a subarray [l, r] with sum s
// We can always get a subarray with sum s - 2
// If a[l] = 2, then we just do [l + 1, r]
// If a[r] = 2, we can do [l, r - 1]
// If a[l] = 1 and a[r] = 1, we can do [l + 1, r - 1]
// Note that the last case won't work if l == r so it won't work if s == 1
// Now we just find the maximum odd and even sum

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
        int N, Q;
        cin >> N >> Q;

        int a[N];
        int twos = 0, ones = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (a[i] == 1) ones++;
            else twos++;
        }

        while (Q--) {
            int op;
            cin >> op;
            if (op == 1) {
                int s;
                cin >> s;
                if (ones > 0) cout << (
                    s <= twos * 2 + ones 
                    ? "YES" : "NO") << endl;
                else cout << (
                    (s <= twos * 2 && s % 2 == 0)
                    ? "YES" : "NO") << endl;
            } else {
                int i, v;
                cin >> i >> v;
                if (a[i - 1] == 1) ones--;
                else twos--;
                if (v == 1) ones++;
                else twos++;
                a[i - 1] = v;
            }
        }
    }
}