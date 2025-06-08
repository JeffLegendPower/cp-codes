// https://codeforces.com/problemset/problem/1766/D

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

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

bool is_prime[10000];
vector<int> primes;
void sieve(int n) {
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; i++) is_prime[i] = true;

    for (int i = 2; i <= n; i++) {
        if (is_prime[i] && (ll) i * i <= n) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }

    for (int i = 2; i <= n; i++) if (is_prime[i]) primes.push_back(i);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;
    sieve(3163);

    while (N--) {
        ll x, y;
        cin >> x >> y;

        ll diff = abs(x-y);
        ll ans = 1e12;
        
        bool found = false;
        for (ll p : primes) {
            if (p*p > diff) break;
            if (diff % p == 0) {
                ll ansp = p - (x % p);
                ans = min(ans, ansp % p);
                found = true;

                ll p2 = diff / p;
                ansp = p2 - (x % p2);
                ans = min(ans, ansp % p2);
            }
        }

        if (!found && diff > 1) {
            ll p = diff;
            ll ansp = p - (x % p);
            ans = min(ans, ansp % p);
        }

        if (ans == 1e12) {
            cout << -1 << endl;
            continue;
        }

        cout << ans << endl;
    }
}