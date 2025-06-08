// https://codeforces.com/contest/1992/problem/E

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
        ll n;
        cin >> n;

        if (n == 1) {
            cout << 9999 << endl;
            for (ll a = 2; a <= 10000; a++) {
                cout << a << " " << (a - 1) << endl;
            }
            continue;
        }


        ll n2 = n;

        ll digits = 0;
        ll powe = 1;
        while (n2 > 0) {
            n2 /= 10;
            digits++;
            powe *= 10;
        }


        vector<pll> works;
        for (ll numdigits = 1; numdigits <= 12; numdigits++) {
            ll target = 0;
            ll numdigits2 = numdigits;
            while (numdigits2 >= digits) {
                numdigits2 -= digits;
                target *= powe;
                target += n;
            }
            target *= powe;
            target += n;
            numdigits2 = digits - numdigits2;
            while (numdigits2 > 0) {
                target /= 10;
                numdigits2--;
            }

            // cout << target << endl;


            ll lowA = 0, highA = 10000;
            ll found = -1;
            while (lowA <= highA) {
                ll midA = lowA + (highA - lowA) / 2;
                ll b = midA * n - target;

                if (digits * midA - b > numdigits) {
                    lowA = midA + 1;
                } else if (digits * midA - b < numdigits) {
                    highA = midA - 1;
                } else {
                    found = midA;
                    break;
                }
            }

            if (found != -1) {
                ll b = found * n - target;
                if (b < 1) continue;
                works.push_back({found, found * n - target});
            }
        }
        // for (ll a = 1; a < 10000; a++) {

        // }

        cout << works.size() << endl;
        for (pll work : works) {
            cout << work.first << " " << work.second << endl;
        }
    }
}