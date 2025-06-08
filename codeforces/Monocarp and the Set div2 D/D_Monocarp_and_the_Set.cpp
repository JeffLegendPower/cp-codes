// https://codeforces.com/problemset/problem/1886/D

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


ll MOD = 998244353;
// Segtree start
const int Nmax = 3e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

ll oper(ll a, ll b) {
    return (a * b) % MOD;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, ll value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 1;
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

    int M;
    cin >> N >> M;

    string s;
    cin >> s;
    for (int i = 0; i < N; i++) t[N + i] = 1;
    for (int i = 1; i < N; i++) if (s[i - 1] == '?') t[N + i] = i - 1;
    build();
    cout << query(0, N) << endl;

    while (M--) {
        int i;
        char c;
        cin >> i >> c;
        i--;

        if (c == '?') modify(i + 1, i);
        else modify(i + 1, 1);
        cout << query(0, N) << endl;
    }
}