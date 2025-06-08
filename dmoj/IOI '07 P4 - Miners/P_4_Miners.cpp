// https://dmoj.ca/problem/ioi07p4

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

bool same[4];

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;
    string s; cin >> s;

    int s2[N];
    for (int i = 0; i < N; i++) {
        if (s[i] == 'M') s2[i] = 0;
        else if (s[i] == 'F') s2[i] = 1;
        else s2[i] = 2;
    }

    // dp[i&1][j][k] = max summ for first i shipments and j and k are mask for the last 2 shipments sent to both mines
    int dp[2][16][16];
    for (int j = 0; j < 16; j++) {
        for (int k = 0; k < 16; k++) {
            dp[0][j][k] = 0;
        }
    }
    
    dp[0][3 + 4*s2[0]][3 + 4*3] = 1;
    dp[0][3 + 4*3][3 + 4*s2[0]] = 1;

    for (int i = 1; i < N; i++) {
        int i2 = i&1;

        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                dp[i2][j][k] = 0;
            }
        }

        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 16; k++) {
                if (dp[i2^1][j][k] == 0) continue;

                int prev11 = j/4, prev12 = j%4, prev21 = k/4, prev22 = k%4;

                same[0] = same[1] = same[2] = same[3] = false;
                same[s2[i]] = true;
                int cnt = 1;
                if (!same[prev11] && prev11 < 3) {
                    cnt++;
                    same[prev11] = true;
                } if (!same[prev12] && prev12 < 3) {
                    cnt++;
                    same[prev12] = true;
                }

                dp[i2][prev11 + 4*s2[i]][k] = max(dp[i2][prev11 + 4*s2[i]][k], cnt + dp[i2^1][j][k]);


                same[0] = same[1] = same[2] = same[3] = false;
                same[s2[i]] = true;
                cnt = 1;
                if (!same[prev21] && prev21 < 3) {
                    cnt++;
                    same[prev21] = true;
                } if (!same[prev22] && prev22 < 3) {
                    cnt++;
                    same[prev22] = true;
                }

                dp[i2][j][prev21 + 4*s2[i]] = max(dp[i2][j][prev21 + 4*s2[i]], cnt + dp[i2^1][j][k]);
            }
        }
    }

    int best = 0;
    for (int j = 0; j < 16; j++) {
        for (int k = 0; k < 16; k++) {
            best = max(best, dp[(N-1)&1][j][k]);
        }
    }

    cout << best;
}