// https://mitit.org/Contest/ViewProblem/monster-fighting?cid=advanced1-2025

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
        int N; cin >> N;

        vector<pll> f(N), e(N);
        for (int i = 0; i < N; i++) cin >> f[i].first >> f[i].second;
        for (int i = 0; i < N; i++) cin >> e[i].first >> e[i].second;

        sort(f.begin(), f.end(), greater<pll>());
        sort(e.begin(), e.end(), greater<pll>());

        vector<ll> light, dark;
        for (int i = 0; i < N; i++) {
            if (e[i].second == 0) light.push_back(e[i].first);
            else dark.push_back(e[i].first);
        }

        bool dp[N+1][N+1];
        for (int i = 0; i <= N; i++) for (int j = 0; j <= N; j++) dp[i][j] = false;
        dp[0][0] = true;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= i; j++) {
                // dp[j][i-j] // from

                if (light.size() > j && dark.size() >= i-j) {
                    bool beatlight = false;
                    if (f[i].second == 0) beatlight = 2*f[i].first >= light[j];
                    else beatlight = f[i].first >= light[j];

                    dp[j+1][i-j] |= beatlight&dp[j][i-j];
                }

                if (dark.size() > i-j && light.size() >= j) {
                    bool beatdark = false;
                    if (f[i].second == 1) beatdark = 2*f[i].first >= dark[j];
                    else beatdark = f[i].first >= dark[j];

                    dp[j][i-j+1] |= beatdark&dp[j][i-j];
                }
            }
        }

        cout << (dp[light.size()][dark.size()] ? "YES" : "NO") << endl;
    }
}