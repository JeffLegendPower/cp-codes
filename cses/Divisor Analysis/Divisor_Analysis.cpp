// https://cses.fi/problemset/task/2182

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


ll MOD = 1e9 + 7;

ll expp(ll a, ll b, ll MOD) {
    ll poww[60];
    poww[0] = a;
    for (int i = 1; i < 60; i++) poww[i] = (poww[i - 1] * poww[i - 1]) % MOD;

    ll res = 1;
    for (int i = 59; i >= 0; i--) {
        if (b & (1ll << i)) {
            res *= poww[i];
            res %= MOD;
        }
    }

    return res;
};

ll mod_inverse(ll num, ll MOD) {
    return expp(num, MOD - 2, MOD);
}

int main() {
    int n;
    cin >> n;

    vector<pll> primefactors(n);
    for (int i = 0; i < n; i++) cin >> primefactors[i].first >> primefactors[i].second;

    // Getting the number of factors is the easiest task of the 3
    // We know that in any factor, a prime factor can appear at most k + 1 times, where k
    // is the power of said prime factor in the prime factorization of n
    // As it can appear 0 times, 1 time, 2 times... k times
    // So just multiply (k_1 + 1) * (k_2 + 1)... to get the number of prime factors
    ll numdiv = 1;
    for (int i = 0; i < n; i++) {
        numdiv *= primefactors[i].second + 1;
        if (numdiv < 0) cout << "E";
        numdiv %= MOD;
    }


    ll proddiv = 1;
    for (int i = 0; i < n; i++) {
        // Similar to in Exponentiation II, since all our operations to find the number of times this prime
        // factor appears in all the factors multiplied together, and then we need to take a power of it
        // And since it's being put under a modulus, we need to put it under MOD - 1, as one can't just take
        // the modulo of a power like that, by Fermat's little theorem, a^(p - 1) = 1 mod (MOD)
        // So we will use it as a^k = a^(k mod (MOD - 1)) mod (MOD)

        // uhh wait we cant rly do this bc 1e9 + 6 has 2 as a factor (cant take mod inverse of 2 mod 1e9+6)
        // and other factors like 500000003 
        ll MULTIMOD = 1e9 + 7 - 1;
        // We will look for how many times this prime factor appears in the product of all factors
        // By first looking at how many times each power of this prime factor appears in the factors
        // (ie. p^1, p^2...)
        ll numfactors = (primefactors[i].second + 1);
        cout << numfactors << endl;
        // Since we know how many factors there are and the same number of factors will have p^0, p^1, and so on
        ll numfactors_inverse = mod_inverse(numfactors, MULTIMOD);
        cout << numfactors_inverse << endl;
        // We can get how many times any power of this prime appears in the list of factors
        ll numdivper = (numdiv * numfactors_inverse) % MULTIMOD;
        cout << numdivper << endl;

        // And then we take the arithmetic sum of the power of the prime factor (1..x)
        // And multiply it by the number of times a power would appear

        ll numdivi = (numdivper * (numfactors - 1)) % MULTIMOD;

        numdivi *= mod_inverse(2, MULTIMOD);
        cout << numdivi << endl;
        numdivi %= MULTIMOD;
        cout << numdivi << endl;
        numdivi *= numfactors;
        cout << numdivi << endl;
        numdivi %= MULTIMOD;
        cout << numdivi << endl;
        cout << numdivi << endl;

        // Finally, multiply in p^numdiv
        // As we now have the sum of powers of prime p in the prime factorization of
        // all the factors, and multiplying them together is just taking the sum of all the powers
        // and exponentiating them
        // cout << numdivi << endl;
        proddiv *= expp(primefactors[i].first, numdivi, MOD);
        cout << proddiv << endl;
        proddiv %= MOD;
    }

    ll sumdiv = 1;
    for (int i = 0; i < n; i++) {
        ll numfactors = primefactors[i].second + 1;

        ll multi = expp(primefactors[i].first, numfactors, MOD);
        multi += MOD - 1;
        multi %= MOD;
        multi *= mod_inverse(primefactors[i].first - 1, MOD);
        multi %= MOD;

        // ll multi = expp(primefactors[i].first, numfactors, MOD);
        // multi += MOD - 1;
        // multi %= MOD;
        sumdiv *= multi;
        // cout << multi << endl;
        sumdiv %= MOD;
    }

    cout << numdiv << " " << sumdiv << " " << proddiv;
}