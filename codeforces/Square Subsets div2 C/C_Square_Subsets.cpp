// https://codeforces.com/contest/895/problem/C

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

ll binpow(ll a, ll b, ll MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int mask[72];

bool prime(int x)
{
	for (int i = 2; i*i <= x; i++)
		if (x%i == 0)
			return 0;
	return 1;
}
 
void init() {
	int cnt = 0;
	for (int i = 2; i < 72; i++)
	{
		if (!prime(i))
			continue;
		for (int j = 1; j < 72; j++)
		{
			int x = j;
			while (x%i == 0)
			{
				x /= i;
				mask[j] ^= (1 << cnt);
			}
		}
		cnt++;
	}
}

int bitmask(int x) {
    int bitmask = 0;

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
    int i = 0;
    for (int prime : primes) {
        int num = 0;
        while (x % prime == 0) {
            x /= prime;
            num++;
        }
        if (num % 2 == 1) bitmask |= 1<<i;
        i++;
    }

    return bitmask;
}

int main() {
    int N;
    cin >> N;

    init();

    ll MOD = 1e9 + 7;

    int cnt[71];
    for (int i = 0; i <= 70; i++) cnt[i] = 0;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    // Number of ways that we can use this number an even amount of times (ways0), and an odd amount of times (ways1)
    ll ways1[71], ways0[71];

    for (int i = 1; i <= 70; i++) {
        if (cnt[i] == 0) {
            ways0[i] = 1;
            ways1[i] = 0;
            continue;
        }

        ll ways = binpow(2, cnt[i] - 1, MOD);
        // ways1[i] = (cnt[i] + 1) / 2;
        // ways0[i] = cnt[i] / 2 + 1;
        ways0[i] = ways;
        ways1[i] = ways;
    }

    // There are only 19 prime numbers <= 70, since 2^19 is small enough, we can use bitmask dp
    // As a set bit can represent a prime number being used an odd amount of times and an unset bit
    // can represent a prime number being used an even amount of times
    // Also instead of using a 2d array of size [70][1<<19], we will use one of size [2][1<<19]
    // to prevent memory overflow as we can just alternate between them and overwrite the dp states
    // as we only need the last state
    // ll dp[2][1<<19];
    vector<ll> dp[2];
    for (int i = 0; i < 2; i++) {
        dp[i] = vector<ll>(1<<19);
    }

    dp[0][0] = 1;
    for (int i = 1; i < 1<<19; i++) dp[0][i] = 0;

    // When multiplying 2 numbers together, the powers in the prime factorizations are added up
    // And since for perfect squares we need the powers to be even AND even + even = even and odd + odd = even
    // and odd + even = odd, we can xor the current parity of prime numbers with that off i to get the next mask
    // And use that to transition, as the number of ways to get that next mask will be the number of ways to get to
    // the previous mask * the number off odd powers of i we can achieve. Since even powers of i will always be squares,
    // We aren't changing the bitmask, so we do the same transition for odd powers except we don't change the mask and
    // its mask * ways to get even power of i

    // Also, we have to keep a 2d array and can't handle it all in 1 array because we can't order the dp transitions
    // in such a way that we don't work with a just-transitioned index and double+ count
    for (int i = 1; i <= 70; i++) {
        // int mask = bitmask(i);
        int cur = i % 2;
        // cout << ways0[i] << " " << ways1[i] << endl;
        for (int j = 0; j < 1<<19; j++) {
            dp[cur][j ^ mask[i]] += dp[(cur + 1) % 2][j] * ways1[i];
            dp[cur][j ^ mask[i]] %= MOD;
            dp[cur][j] += dp[(cur + 1) % 2][j] * ways0[i];
            dp[cur][j] %= MOD;
        } for (int j = 0; j < 1<<19; j++) dp[(cur + 1) % 2][j] = 0;

        // cout << dp[i][0] << endl;
    }

    cout << (dp[0][0] - 1 + MOD) % MOD;
}