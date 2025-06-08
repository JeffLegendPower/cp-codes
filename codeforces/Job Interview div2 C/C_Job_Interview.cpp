// https://codeforces.com/problemset/problem/1976/C

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;

        pll c[N+M+1];
        ll a[N+M+1], b[N+M+1];
        for (int i = 0; i < N+M+1; i++) cin >> a[i];
        for (int i = 0; i < N+M+1; i++) cin >> b[i];

        ll ans = 0;
        int n = 0, m = 0;
        int first = N+M;
        int ab = -1;
        if (n == N) ab = 1;
        else if (m == M) ab = 0;

        for (int i = 0; i < N+M+1; i++) {
            if (ab == 0) {
                if (a[i] < b[i]) first = min(first, i);
                ans += a[i];
            } else if (ab == 1) {
                if (b[i] < a[i]) first = min(first, i);
                ans += b[i];
            }
            else if (a[i] > b[i]) {
                ans += a[i];
                n++;
                if (n == N) ab = 1;
            } else {
                ans += b[i];
                m++;
                if (m == M) ab = 0;
            }
        }

        cout << first << endl;
        for (int i = 0; i < N+M+1; i++) {
            if (i < first) {
                if (a[i] > b[i]) cout << ans - a[i] - min(a[first], b[first]) + a[first] << " ";
                else cout << ans - b[i] - min(a[first], b[first]) + b[first] << " ";
            } else {
                if (ab == 0) cout << ans - a[i] << " ";
                else cout << ans - b[i] << " ";
            }
        }
    }
}