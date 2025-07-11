// https://codeforces.com/problemset/problem/1516/D

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
bitset<9592> t[2 * Nmax];

void oper(bitset<9592>& a, bitset<9592>& b, bitset<9592>& c) {
    // return a + b;
    
}

// void build() {  // build the tree
//   for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
// }

// int query(int l, int r) {  // on interval [l, r)
//   int res = 0;
//   for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
//     if (l&1) res = oper(res, t[l++]);
//     if (r&1) res = oper(res, t[--r]);
//   }
//   return res;
// }
// Segtree end

vector<int> primes;
vector<bool> prime;

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
        if (prime[i]) primes.push_back(i);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    sieve(100000);
}