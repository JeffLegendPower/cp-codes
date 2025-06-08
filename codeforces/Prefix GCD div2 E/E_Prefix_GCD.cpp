// https://codeforces.com/contest/2013/problem/E

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll N; cin >> N;

        ll a[N];
        ll gcdd = 1e6;
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            gcdd = min(gcdd, a[i]);
        }

        ll total = gcdd;
        // gcd will converge in at most log_2(1e5) operations so we can run naive up to that
        // as gcd will at least keep dividing by 2 until convergence

        // edi proves convergence in 10 operations (actually 7 operations)
        // as first 6 primes such that their product is <= 1e5
        // + 1 for initial
        // as when you divide each term by gcd(entire array) so your gcd converges to 1, you drop a prime each time when
        // greedily gcding
        
        // also greedily minimizing gcd is optimal because when u greedily minimize gcd, it doesn't make it impossible
        // for the next gcd to be minimal
        
        for (int i = 1; i < min(17ll, N); i++) {

            ll nextgcdd = gcdd;
            for (int j = 0; j < N; j++) {
                nextgcdd = min(nextgcdd, gcd(gcdd, a[j]));
            }

            total += nextgcdd;
            gcdd = nextgcdd;
        }

        if (N > 17) total += gcdd * (N - 17ll);

        cout << total << endl;
    }
}