// https://dmoj.ca/problem/ccc11s4

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

void calc(ll &total, ll &in, ll &out) {
    ll diff = min(in, out);
    total += diff;
    in -= diff;
    out -= diff;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll o0, o1, a0, a1, b0, b1, ab0, ab1;
    ll io0, io1, ia0, ia1, ib0, ib1, iab0, iab1;

    cin >> o0 >> o1 >> a0 >> a1 >> b0 >> b1 >> ab0 >> ab1;
    cin >> io0 >> io1 >> ia0 >> ia1 >> ib0 >> ib1 >> iab0 >> iab1;

    ll total = 0;

    calc(total, o0, io0);

    calc(total, a0, ia0);
    calc(total, b0, ib0);

    calc(total, o0, ia0);
    calc(total, o0, ib0);

    calc(total, ab0, iab0);
    calc(total, a0, iab0);
    calc(total, b0, iab0);
    calc(total, o0, iab0);


    calc(total, o0, io1);
    calc(total, o1, io1);

    calc(total, a0, ia1);
    calc(total, b0, ib1);
    calc(total, a1, ia1);
    calc(total, b1, ib1);

    calc(total, o0, ia1);
    calc(total, o0, ib1);
    calc(total, o1, ia1);
    calc(total, o1, ib1);

    calc(total, ab0, iab1);
    calc(total, a0, iab1);
    calc(total, b0, iab1);
    calc(total, o0, iab1);
    calc(total, ab1, iab1);
    calc(total, a1, iab1);
    calc(total, b1, iab1);
    calc(total, o1, iab1);

    cout << total;
}