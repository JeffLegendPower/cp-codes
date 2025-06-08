// https://usaco.org/index.php?page=viewproblem2&cpid=1185

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

ll MOD = 1e9 + 7;
int H[100];

ll dpsum() {
    // num choices of hunger levels mod MOD from cows 1 to i, where the hunger level of cow i is j
    // dp[i][j]
    // to optimize the transition time from O(H) to O(1), we will store the dp as prefix sums
    vector<ll> dp[N];

    for (int h = 0; h <= H[0]; h++) {
        dp[0].push_back(1);
    }

    for (int i = 1; i < N; i++) {
        for (int h = 0; h <= H[i]; h++) {
            if (h > H[i - 1]) {
                dp[i].push_back(dp[i].back());
                continue;
            }

            ll ways = dp[i - 1][H[i - 1] - h];
            if (h > 0) dp[i].push_back((dp[i].back() + ways) % MOD);
            else dp[i].push_back(ways);
        }
    }

    return dp[N - 1].back();
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    // if N is odd, then we need to solve for # when each end hunger is x
    // and sum them
    // if N is even, then we only need to solve for # when end hunger is 0
    // because when N is even we can decrement every element by a constant number
    cin >> N;

    int minH = 1e6;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
        minH = min(minH, H[i]);
    }

    ll total = 0;
    if (N % 2 == 0) total = dpsum();
    else {
        for (int h = 0; h <= minH; h++) {
            total = (total + dpsum()) % MOD;
            for (int i = 0; i < N; i++) H[i]--;
        }
    }

    cout << total;
}