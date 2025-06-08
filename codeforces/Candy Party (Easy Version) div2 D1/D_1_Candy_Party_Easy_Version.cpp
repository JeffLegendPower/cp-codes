// https://codeforces.com/contest/1869/problem/D1

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
        int N;
        cin >> N;

        ll a[N];
        ll total = 0;

        for (int i = 0; i < N; i++) {
            cin >> a[i];
            total += a[i];
        }

        if (total % N > 0) {
            cout << "No" << endl;
            continue;
        }

        ll each = total / N;

        bool works = true;

        // incoming candy, outgoing candy
        pii req[N];
        for (int i = 0; i < N; i++) {
            ll diff = abs(each - a[i]);

            int y = 0, x = 0;
            int strandstart = 0;
            for (int j = 0; j < 30; j++) {
                if (diff & (1ll << j)) {
                    if (strandstart == 0) {
                        strandstart = 1;
                        y = j;
                    } else if (strandstart == 2) {
                        works = false;
                        goto end;
                    }
                } else if (strandstart == 1) {
                    strandstart = 2;
                    x = j;
                }
            }

            if (each == a[i]) {
                req[i] = {-1, -1};
                continue;
            }
            if (each < a[i]) {
                int temp = y;
                y = x;
                x = temp;
            }
            req[i] = {x, y};
        }

        int counts[30];
        for (int i = 0; i < 30; i++) counts[i] = 0;
        for (int i = 0; i < N; i++) {
            if (req[i].first == -1) continue;
            counts[req[i].first]--;
            counts[req[i].second]++;
        }

        for (int i = 0; i < 30; i++) if (counts[i] != 0) works = false;

        end:
        cout << (works ? "Yes" : "No") << endl;
    }
}