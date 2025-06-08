// https://codeforces.com/contest/1878/problem/F

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

    sieve(1e6);

    while (T--) {
        ll n;
        int Q;
        cin >> n >> Q;

        map<ll, ll> cntprimes;

        for (ll prime : all_primes) {
            if (prime > sqrt(n)) break;
            ll cnt = 0;
            while (n % prime == 0) {
                n /= prime;
                cnt++;
            }
            cntprimes[prime] += cnt;

            // cout << prime << " " << cnt << endl;
        }
        if (n > 1) cntprimes[n]++;

        ll numfactors = 1;

        for (auto itr = cntprimes.begin(); itr != cntprimes.end(); itr++) {
            numfactors *= itr->second + 1;
        }

        // a only exists when d(n) is a factor of n
        // when n % d(n) == 0

        map<ll, ll> cntprimes2(cntprimes);
        ll numfactors2 = numfactors;

        while (Q--) {
            int k;
            cin >> k;

            if (k == 2) {
                cntprimes2.clear();
                cntprimes2.insert(cntprimes.begin(), cntprimes.end());
                numfactors2 = numfactors;
                continue;
            }

            ll x;
            cin >> x;
            for (ll prime : all_primes) {
                if (prime > sqrt(x)) break;
                ll cnt = 0;
                while (x % prime == 0) {
                    x /= prime;
                    cnt++;
                }

                numfactors2 += cnt * (numfactors2 / (cntprimes2[prime] + 1));
                cntprimes2[prime] += cnt;
            }

            // cout << x << endl;

            if (x > 1) {
                numfactors2 += numfactors2 / (cntprimes2[x] + 1);
                cntprimes2[x]++;
            }



            ll numfactors3 = numfactors2;
            bool factor = true;
            for (ll prime : all_primes) {
                if (prime > sqrt(numfactors3)) break;
                ll cnt = 0;
                while (numfactors3 % prime == 0) {
                    numfactors3 /= prime;
                    cnt++;
                }

                if (cnt > cntprimes2[prime]) {
                    // cout << prime << endl;
                    factor = false;
                }
            }

            if (numfactors3 > 1 && 1 > cntprimes2[numfactors3]) {
                factor = false;
                // cout << numfactors3 << " " << cntprimes2[numfactors3] << endl;
            }


            if (factor) cout << "YES" << endl;
            else cout << "NO" << endl;
        }

        cout << endl;
    }
}