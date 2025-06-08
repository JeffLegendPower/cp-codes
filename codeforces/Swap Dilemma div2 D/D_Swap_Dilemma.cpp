// https://codeforces.com/contest/1983/problem/D

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
    bool operator() (int a, int b) {
        return a > b;
    }
};

typedef tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


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
        map<int, int> bidxs;
        bool works = true;

        for (int i = 0; i < N; i++) {
            cin >> a[i];
        } for (int i = 0; i < N; i++) {
            cin >> b[i];
            bidxs[b[i]] = i + 1;
        }

        int totaldist = 0;
        // set<int> movedidxs;
        ordered_set movedidxs;
        for (int i = 0; i < N - 1; i++) {
            int curidx = bidxs[a[i]];
            if (curidx == 0) {
                works = false;
                goto end;
            }

            // auto it = movedidxs.upper_bound(curidx);
            // int num = distance(it, movedidxs.end());
            int num = movedidxs.order_of_key(curidx);
            movedidxs.insert(curidx);
            curidx += num;
            totaldist += curidx - i - 1;
            cout << curidx << " " << num << " " << totaldist << endl;
        }

        if (totaldist % 2 == 1) works = false;
        // cout << totaldist << endl;

        end:
        cout << (works ? "YES" : "NO") << endl;
    }
}