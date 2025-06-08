// https://codeforces.com/problemset/problem/1493/D

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
    bool operator() (const plli& a, const plli& b) const {
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

vector<ll> primes;
vector<bool> prime;

void sieve(int n) {
    prime.resize(n + 1, true);

    for (int p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (int i = p * p; i <= n; i += p) {
                prime[i] = false;
            }
        }
    } for (int i = 2; i <= n; i++) if (prime[i]) primes.push_back(i);
}

ll MOD = 1e9 + 7;

ll binpow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
} ll modinv(ll x) {
    return binpow(x, MOD - 2);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    sieve(200000);

    int N, Q;
    cin >> N >> Q;

    int nump = primes.size();

    // {cnt, idx}
    vector<set<pii>> primecnts(nump);
    // [idx]: cnt
    vector<unordered_map<int, int>> acnts(nump);

    for (int i = 0; i < N; i++) {
        ll a; cin >> a;

        int j = -1;
        for (ll p : primes) {
            j++;
            if (p * p > a) break;

            int cnt = 0;
            while (a % p == 0) {
                a /= p;
                cnt++;
            }

            if (cnt > 0) {
                primecnts[j].insert({cnt, i});
                acnts[j][i] = cnt;
            }
        }

        if (a > 1) {
            j = lower_bound(primes.begin(), primes.end(), a) - primes.begin();
            primecnts[j].insert({1, i});
            acnts[j][i] = 1;
        }
    }

    ll f = 1;
    for (int i = 0; i < nump; i++) {
        auto st = primecnts[i].begin();
        if (primecnts[i].size() < N) continue;
        if (st != primecnts[i].end()) f = (f * binpow(primes[i], st->first)) % MOD;
    }

    while (Q--) {
        int i;
        ll x;
        cin >> i >> x;

        i--;

        int j = -1;
        for (ll p : primes) {
            j++;
            if (p * p > x) break;

            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }

            if (cnt > 0) {
                auto st = primecnts[j].begin();
                if (primecnts[j].size() == N && st != primecnts[j].end()) f = (f * modinv(binpow(primes[j], st->first))) % MOD;

                primecnts[j].erase({acnts[j][i], i});
                acnts[j][i] += cnt;

                primecnts[j].insert({acnts[j][i], i});
                st = primecnts[j].begin();
                if (primecnts[j].size() == N && st != primecnts[j].end()) f = (f * binpow(primes[j], st->first)) % MOD;
            }
        }

        if (x > 1) {
            j = lower_bound(primes.begin(), primes.end(), x) - primes.begin();

            auto st = primecnts[j].begin();
            if (primecnts[j].size() == N && st != primecnts[j].end()) f = (f * modinv(binpow(primes[j], st->first))) % MOD;

            primecnts[j].erase({acnts[j][i], i});
            acnts[j][i] += 1;

            primecnts[j].insert({acnts[j][i], i});
            st = primecnts[j].begin();
            if (primecnts[j].size() == N && st != primecnts[j].end()) f = (f * binpow(primes[j], st->first)) % MOD;
        }

        cout << f << endl;
    }
}