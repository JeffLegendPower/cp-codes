// https://codeforces.com/contest/1989/problem/B

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
        string a, b;
        cin >> a >> b;

        int inter = 0;
        for (int i = 0; i < b.size(); i++) {
            int num = 0;
            int aidx = 0;
            for (int j = i; j < b.size(); j++) {
                while (aidx < a.size() && a[aidx] != b[j]) aidx++;
                if (aidx == a.size()) break;
                aidx++;
                num++;
            }
            // cout << num << endl;

            inter = max(inter, num);
        }
        cout << a.size() + b.size() - inter << endl;

        // int size = 0;
        // int aidx = 0, bidx = 0;

        // while (bidx < N) {
        //     if (b[bidx] == a[aidx]) {
        //         aidx++;
        //     }

        //     bidx++;
        // }

        // cout << aidx << " " << bidx << endl;
    }
}