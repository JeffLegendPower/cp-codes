// https://cses.fi/problemset/task/1713

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
        int x;
        cin >> x;

        if (x == 1) {
            cout << 1 << endl;
            continue;
        }

        vector<int> factors;
        factors.push_back(0);
        int backidx = 0;

        while (x % 2 == 0) {
            x /= 2;
            factors[backidx]++;
        }
        if (factors[backidx] > 0) {
            factors.push_back(0);
            backidx++;
        }

        for (int i = 3; i <= ceil(sqrt(x)); i += 2) {
            while (x % i == 0) {
                x /= i;
                factors[backidx]++;
            }
            if (factors[backidx] > 0) {
                factors.push_back(0);
                backidx++;
            }
        }

        if (x != 1) factors[backidx]++;

        if (factors.size() == 1) {
            cout << 2 << endl;
        } else {
            ll divisors = 1;
            for (int numfactor : factors) divisors *= numfactor + 1;
            cout << divisors << endl;
        }
    }
}