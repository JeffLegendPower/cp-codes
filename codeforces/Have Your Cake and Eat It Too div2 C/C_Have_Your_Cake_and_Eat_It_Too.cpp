// https://codeforces.com/contest/1983/problem/C

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

        ll a[N], b[N], c[N];
        ll prea[N + 1], preb[N + 1], prec[N + 1];
        prea[0] = 0, preb[0] = 0, prec[0] = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            prea[i + 1] = prea[i] + a[i];
        } for (int i = 0; i < N; i++) {
            cin >> b[i];
            preb[i + 1] = preb[i] + b[i];
        } for (int i = 0; i < N; i++) {
            cin >> c[i];
            prec[i + 1] = prec[i] + c[i];
        }

        ll target = prea[N] / 3;
        if (prea[N] % 3 > 0) target++;
        bool found = false;

        int bstart = N - 1;
        int high = N - 1, low = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (preb[mid + 1] >= target) {
                high = mid - 1;
                bstart = min(bstart, mid);
            } else low = mid + 1;
        } 
        int cstart = N - 1;
        high = N - 1, low = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (prec[mid + 1] >= target) {
                high = mid - 1;
                cstart = min(cstart, mid);
            } else low = mid + 1;
        }

        int bend = 0;
        high = N - 1, low = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (preb[N] - preb[mid] >= target) {
                low = mid + 1;
                bend = max(bend, mid);
            } else high = mid - 1;
        }
        int cend = 0;
        high = N - 1, low = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (prec[N] - prec[mid] >= target) {
                low = mid + 1;
                cend = max(cend, mid);
            } else high = mid - 1;
        }


        for (int alow = 0; alow < N; alow++) {
            int low = alow, high = N - 1;
            int ahigh = N;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                ll pre = prea[mid + 1] - prea[alow];
                if (pre >= target) {
                    ahigh = min(ahigh, mid);
                    high = mid - 1;
                } else low = mid + 1;
            }
            if (ahigh == N) goto end;
            if (alow > 0) {
                if (ahigh < N - 1) {
                    if (preb[alow] >= target && prec[N] - prec[ahigh + 1] >= target) {
                        found = true;
                        cout << alow + 1 << " " << ahigh + 1 << " " << 1 << " " << alow << " " << ahigh + 2 << " " << N << endl;
                        goto end;
                    } if (prec[alow] >= target && preb[N] - preb[ahigh + 1] >= target) {
                        found = true;
                        cout << alow + 1 << " " << ahigh + 1 << " " << ahigh + 2 << " " << N << " " << 1 << " " << alow << endl;
                        goto end;
                    }
                }
            }

            if (alow > bstart && prec[alow] - prec[bstart + 1] >= target) {
                found = true;
                cout << alow + 1 << " " << ahigh + 1 << " " << 1 << " " << bstart + 1 << " " << bstart + 2 << " " << alow << endl; 
                goto end;
            } if (alow > cstart && preb[alow] - preb[cstart + 1] >= target) {
                found = true;
                cout << alow + 1 << " " << ahigh + 1 << " " << cstart + 2 << " " << alow << " " << 1 << " " << cstart + 1 << endl; 
                goto end;
            } if (ahigh < bend && prec[bend] - prec[ahigh + 1] >= target) {
                found = true;
                cout << alow + 1 << " " << ahigh + 1 << " " << bend + 1 << " " << N << " " << ahigh + 2 << " " << bend << endl;
                goto end;
            } if (ahigh < cend && preb[cend] - preb[ahigh + 1] >= target) {
                found = true;
                cout << alow + 1 << " " << ahigh + 1 << " " << ahigh + 2 << " " << cend << " " << cend + 1 << " " << N << endl;
                goto end;
            }
        }

        end:
        if (!found) cout << -1 << endl;
    }
}