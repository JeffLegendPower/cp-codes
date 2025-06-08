// https://codeforces.com/contest/1316/problem/E

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

struct ppl {
    ll a;
    vector<ll> s;
};

const int MAXN = 1e5, MAXP = 7;
ll dp[MAXN + 1][1 << MAXP];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, p, k;
    cin >> N >> p >> k;

    ppl people[N];
    for (int i = 0; i < N; i++) cin >> people[i].a;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < p; j++) {
            ll s;
            cin >> s;
            people[i].s.push_back(s);
        }
    }

    sort(people, people + N, [](ppl one, ppl two) {
        return one.a > two.a;
    });

    for (int i = 0; i < N; i++) {
        for (int num = min(i, p); num >= 0; num--) {
            for (int msk = 0; msk < (1<<p); msk++) {
                if (__builtin_popcount(msk) != num) continue;

                if (i - num < k) dp[i + 1][msk] = max(dp[i + 1][msk], dp[i][msk] + people[i].a);
                else dp[i + 1][msk] = max(dp[i + 1][msk], dp[i][msk]);

                for (int next = 0; next < p; next++) {
                    if (msk & (1<<next)) continue;

                    dp[i + 1][msk | (1<<next)] = max(dp[i + 1][msk | (1<<next)], 
                        dp[i][msk] + people[i].s[next]
                    );
                }
            }
        }
    }

    cout << dp[N][(1<<p) - 1];
}