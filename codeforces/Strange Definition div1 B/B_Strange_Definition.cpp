// https://codeforces.com/contest/1470/problem/B

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
vector<ll> all_primes;

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

    int T2 = T;
    ll qs = 0;

    sieve(1000000);

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        ll A = 0;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            A = max(A, a[i]);
        }

        sort(a, a + N);
        map<int, vector<int>> idxs;
        for (int i = 0; i < N; i++) idxs[a[i]].push_back(i);

        DSU dsu(N);

        ll a2[N];

        for (int i = 0; i < N; i++) {
            ll num = a[i];
            ll res1 = sqrt(num);

            ll base = 1;
            for (ll prime : all_primes) {
                if (prime > res1) break;
                int cnt = 0;
                while (num % prime == 0) {
                    cnt++;
                    num /= prime;
                }
                if (cnt % 2 == 1) base *= prime;
            }
            base *= num;
            a2[i] = base;
        }

        sort(a2, a2 + N);

        int ones = 0;
        int evens = 0;
        int most = 0;

        int l = 0;

        while (l < N) {
            int r = l;
            ll num = a2[r];

            int cnt = 0;

            while (r < N && a2[r] == num) {
                cnt++;
                r++;
            }
            l = r;

            most = max(most, cnt);
            if (num == 1) ones += cnt;
            else if (cnt % 2 == 0) evens += cnt;
        }

        ll Q;
        cin >> Q;

        while (Q--) {
            ll w;
            cin >> w;

            if (w == 0) cout << most << endl;
            else cout << max(most, evens + ones) << endl;
        }
    }
}