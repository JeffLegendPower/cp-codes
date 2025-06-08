// https://usaco.org/index.php?page=viewproblem&cpid=1438

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

ll MOD = 1e9 + 7;

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;
    string s; cin >> s;

    int rpre[N + 1], bpre[N + 1];
    rpre[0] = 0, bpre[0] = 0;
    vector<int> reds;

    for (int i = 0; i < N; i++) {
        rpre[i + 1] = rpre[i];
        bpre[i + 1] = bpre[i];
        if (s[i] == 'R') rpre[i + 1]++;
        else if (s[i] == 'B') bpre[i + 1]++;

        if (s[i] == 'R') reds.push_back(i);
    }

    vector<ll> dp(N + 1, 0);
    dp[0] = 1;

    vector<ll> prop(N + 1000, 0);
    for (int i = 0; i < N; i++) {
        if (s[i] == 'X') dp[i + 1] = (dp[i + 1] + dp[i]) % MOD;

        if (i > 1) prop[i] += prop[i - 2];
        dp[i + 1] = (dp[i + 1] + prop[i]) % MOD; 


        // Upper bound on the value of x
        // if for some x there is some B in [i, i+x - 1], then there will be some B
        // for all x2 > x, which means we can set an upper bound on x
        int low = 1, high = (N - i)/2;
        int best = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (bpre[i+mid] - bpre[i] > 0) high = mid - 1;
            else {
                low = mid + 1;
                best = mid;
            }
        }

        auto nextr = upper_bound(reds.begin(), reds.end(), i);
        int idx = nextr - reds.begin();

        ll minx = 0;
        for (; idx < reds.size(); idx++) {
            ll x = (reds[idx] - i)/2;
            cout << x << endl;
            if (x > minx) {
                prop[i + 1] += dp[i];
                prop[i + 2 * minx + 1] -= dp[i];
            }

            minx = reds[idx] + 1 - i;
        }

        prop[i + ]
        
        // for (int x = 1; x <= best; x++) {
        //     if (bpre[i+x] - bpre[i] > 0) continue;

        //     if (rpre[i+2*x] - rpre[i+x] > 0) continue;


        //     dp[i + 2*x] = (dp[i + 2*x] + dp[i]) % MOD;
        // }
    }

    cout << endl;
    for (int i = 0; i < N; i++) cout << dp[i] << endl;
    cout << dp[N] << endl;
}