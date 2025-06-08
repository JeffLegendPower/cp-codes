// https://codeforces.com/problemset/problem/1846/E2

// We will solve this for each n
// We first need to notice that the number of vertices in
// a graph which is expanded by x vertices k times
// Can be written as 1 + x + x^2 + x^3 ... + x^k
// Now we will iterate through each 2 <= k < 60
// As we must expand atleast 2 times and expanding more than 59 times
// will go over the bound for n which is useless for us as x >= 2
// So while iterating through each k, we can say the polynomial expansion = n
// Then subtract n from both sides so we have 1 - n + x + x^2... +x^k = 0
// Since we need a positive integer solution for this equation
// AND since this equation is strictly increasing from x > 0
// AND will have 1 solution
// We can binary search x to find the positive solution to the equation
// And if it's an integer, then we have a valid solution
// Also we have to greedily bound x in our binary search for every k as otherwise the solution
// would TLE

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

bool overflow = false;
long double poly(ll k, ll target, ll x) {
    long double result = 1 - target;

    ll powe = x;
    for (int i = 1; i <= k; i++) {
        result += powe;
        if (result < 1 - target || powe < 0) overflow = true;
        powe *= x;
    }
    return result;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        ll n;
        cin >> n;

        bool works = false;

        for (int k = 2; k < 60; k++) {
            ll low = 2, high = 10;

            ll expo = ceil(18.0 / k);
            for (int i = 1; i < expo; i++) high *= 10;

            ll best = -1;
            while (low <= high) {
                ll mid = low + (high - low) / 2;
                overflow = false;
                long double res = poly(k, n, mid);

                if (overflow) {
                    high = mid - 1;
                    continue;
                }

                if (abs(res) < 0.00001) {
                    best = mid;
                    break;
                } else if (res < 0) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            if (best != -1) {
                works = true;
                break;
            }
        }

        cout << (works ? "YES" : "NO") << endl;
    }
}