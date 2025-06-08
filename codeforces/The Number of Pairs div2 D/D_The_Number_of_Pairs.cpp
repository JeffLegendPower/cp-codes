// https://codeforces.com/contest/1499/problem/D

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    // allows us to precalculate and avoid O(n) time per testcase
    vector<bool> is_prime(2e7 + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= 2e7; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 2e7; j += i) is_prime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= 2e7; i++) if (is_prime[i]) primes.push_back(i);

    vector<ll> add(2e7 + 1, 1);
    for (int p : primes) {
        for (int j = p; j <= 2e7; j += p) add[j] *= 2;
    }

    int T;
    cin >> T;

    while (T--) {
        ll c, d, x;
        cin >> c >> d >> x;

        ll total = 0;

        for (ll gcdd = 1; gcdd * gcdd <= x; gcdd++) {
            // gcd(a, b) must be a factor of x by this
            // lcm(a, b) = gcd * multi
            // so c * k * gcd - d * gcd = x
            // x = gcd * (c * k - d)
            // x must be a multiple of gcd
            if (x % gcdd != 0) continue;

            ll x2 = x / gcdd;
            x2 += d;

            if (x2 % c == 0) {
                // lcm = gcd * multi
                ll multi = x2 / c;

                total += add[multi];
            }

            if (x / gcdd == gcdd) continue;
            
            ll gcdd2 = x / gcdd;
            x2 = x / gcdd2;
            x2 += d;

            if (x2 % c == 0) {
                ll multi = x2 / c;

                total += add[multi];
            }
        }

        cout << total << endl;
    }
}