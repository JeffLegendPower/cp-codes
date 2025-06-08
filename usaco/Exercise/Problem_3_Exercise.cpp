// https://usaco.org/index.php?page=viewproblem2&cpid=1043

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

    setIO("exercise");

    int N;
    ll M;
    cin >> N >> M;

    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i) is_prime[j] = false;
        }
    }

    vector<ll> primes;
    for (int i = 2; i <= N; i++) if (is_prime[i]) primes.push_back(i);

    ll sums[N + 1][2];
    for (int i = 1; i <= N; i++) sums[i][0] = 0;

    sums[0][0] = 1;

    int idx = 0;
    for (ll p : primes) {
        ll ppow = 1;

        idx ^= 1;

        for (int i = 0; i <= N; i++) sums[i][idx] = sums[i][idx ^ 1];

        while (ppow * p <= N) {
            ppow *= p;

            for (int i = N; i >= ppow; i--) {
                sums[i][idx] = (sums[i][idx] + sums[i - ppow][idx ^ 1] * ppow) % M;
            }
        }
    }

    ll total = 0;
    for (int i = 0; i <= N; i++) {
        total = (total + sums[i][idx]) % M;
    }

    cout << total;
}