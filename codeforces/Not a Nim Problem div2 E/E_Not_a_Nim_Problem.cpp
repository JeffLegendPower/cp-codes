// https://mirror.codeforces.com/contest/2004/problem/E

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
vector<bool> prime;
vector<int> all_primes;

// Sieve of Eratosthenes
void sieve(int n) {
    prime.resize(n + 1);

    std::fill(prime.begin(), prime.end(), true);
    for (int p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    for (int i = 2; i <= n; i++) {
        if (prime[i]) all_primes.push_back(i);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    sieve(1e7);

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        for (int i = 0; i < N; i++) cin >> a[i];

        ll primecnt[N];
        for (int i = 0; i < N; i++) {
            primecnt[i] = -1;
            for (int prime : all_primes) {
                if (prime * prime > a[i]) break;
                if (a[i] % prime == 0) {
                    primecnt[i] = a[i] / prime;
                    break;
                }
            }

            if (primecnt[i] == -1) primecnt[i] = 1;
        }

        ll res = 0;
        for (int i = 0; i < N; i++) cout << primecnt[i] << " ";
        // for (int i = 0; i < N; i++) res ^= primecnt[i];
        // cout << endl;
        cout << res << endl;

    }
}