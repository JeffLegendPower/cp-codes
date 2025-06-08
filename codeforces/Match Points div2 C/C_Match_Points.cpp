// https://codeforces.com/contest/1156/problem/C

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

int Ni;
ll zi;
vector<ll> xi;
void randgen() {
    random_device rd;  // Seed for random number generator
    mt19937 gen(rd()); // Mersenne Twister random number engine

    // Define the ranges for N and z
    uniform_int_distribution<int> dist_N(2, 6);
    uniform_int_distribution<int> dist_z(1, 10);
    uniform_int_distribution<int> dist_x(1, 10);

    // Generate N and z
    Ni = dist_N(gen);
    zi = dist_z(gen);

    // Generate N random numbers in the range [1, 1e9]
    for (int i = 0; i < Ni; ++i) {
        xi.push_back(dist_x(gen));
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    ll z;
    cin >> N >> z;

    ll x[N];
    for (int i = 0; i < N; i++) cin >> x[i];
    sort(x, x + N);
    int i2 = N / 2;

    int pairs = 0;
    for (int i = 0; i < N / 2; i++) {
        while (i2 < N && abs(x[i2] - x[i]) < z) i2++;
        if (i2 < N) {
            pairs++;
            i2++;
        }
    }

    cout << pairs << endl;
}