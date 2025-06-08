// https://codeforces.com/contest/1896/problem/C

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
struct val {
    int a, idx;
};

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, x;
        cin >> N >> x;

        val a[N], b[N];
        FOR(i, 0, N) {
            cin >> a[i].a;
            a[i].idx = i;
        } FOR(i, 0, N) {
            cin >> b[i].a;
            b[i].idx = i;
        }

        sort(a, a + N, [](val one, val two) {
            return one.a < two.a;
        }); sort(b, b + N, [](val one, val two) {
            return one.a < two.a;
        });

        int most = 0;
        int least = 0;
        int bidx = N - 1;
        FOR(i, 0, N) {
            if (a[i].a > b[i].a) most++;
            if (a[N - 1 - i].a > b[bidx].a) least++;
            else bidx--;
        }

        if (x < least || x > most) {
            cout << "NO" << endl;
            continue;
        }

        int fixed[N];
        int needed = N - x;
        int cur = 0;
        int left = 0, right = N - 1;
        FOR(i, 0, N) fixed[i] = -1;

        FOR(i, 0, N) {
            if (cur < needed) {
                if (a[N - 1 - i].a > b[right].a)
                    fixed[a[N - 1 - i].idx] = b[left++].a;
                else fixed[a[N - 1 - i].idx] = b[right--].a;
                cur++;
            } else {
                // fixed[a[i].idx] = b[left++].a;
            }
        }

        cout << "YES" << endl;
        for (int i = 0; i < N; i++) cout << fixed[i] << " ";
        cout << endl;

        cout << least << " " << most << " " << x << endl;
    }
}