// https://codeforces.com/problemset/problem/1848/D

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

ll addd(ll s, ll num) {
    s += 20 * (num / 4);
    num %= 4;

    while (num > 0) {
        s += s % 10;
        num--;
    }

    return s;
}

// (s + 20x) * (k - 4x) = sk - 4sx + 20kx - 80x^2
// = -80x^2 + (20k - 4s)x + sk
// vertex x: (20k - 4s)/160
ll sktest(ll s, ll k) {
    ll vertex = (20ll*k - 4ll*s) / 160ll;
    vertex = max(vertex, 0ll);
    ll ans = (s + 20ll*vertex) * (k - 4ll*vertex);
    ans = max(ans, (s + 20ll*(vertex + 1)) * (k - 4ll*(vertex + 1)));
    return ans;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;

    int T2 = T;
    bool tc5 = false;

    while (T--) {
        ll s, k;
        cin >> s >> k;

        if ((s%10) == 0) {
            cout << s*k << endl;
            continue;
        } if ((s%10) == 5) {
            cout << max(s*k, (s+5)*(k-1)) << endl;
            continue;
        }

        ll best = s*k;

        if (s&1) {
            s += s % 10;
            k--;
        }

        for (int i = 0; i < 4; i++) {
            if (i > 0) {
                s += s % 10;
                k--;
            } if (k <= 0) break;

            best = max(best, sktest(s, k));
        }

        cout << best << endl;
    }
}