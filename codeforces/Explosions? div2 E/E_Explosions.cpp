// https://codeforces.com/problemset/problem/1795/E

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
const int Nmax = 3e5;  // limit for array size
int N;  // array size
ll t[2 * Nmax];

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
}

ll query(int l, int r) {  // on interval [l, r)
  ll res = 1e18;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = min(res, t[l++]);
    if (r&1) res = min(res, t[--r]);
  }
  return res;
}
// Segtree end

vector<ll> h;
vector<ll> res;

void calculate() {
    ll pre[N + 1], minpre[N + 1];
    pre[0] = 0;
    minpre[0] = 1e18;

    for (int i = 0; i < N; i++) {
        t[N + i] = h[i] - i;
        pre[i + 1] = pre[i] + h[i];
    }

    build();
    
    // min basic spell to be able to explode whole side left of i (not including explode spell cost)
    res.push_back(0);

    for (ll i = 1; i < N; i++) {
        ll a = h[i];

        // we need to find the rightmost j < i such that h[j] <= h[i] - (i - j)
        // = h[j] - j <= h[i] - i
        // we can do this with minimum prefix and binary search

        ll target = a - i;
        ll low = max(0ll, i - h[i]), high = i - 1;
        ll best = max(-1ll, i - h[i] - 1);
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (query(mid, i) <= target) {
                low = mid + 1;
                best = mid;
            } else high = mid - 1;
        }

        ll ans = pre[i] - pre[best + 1];
        ans -= (i - best - 1) * (h[i] - 1 + h[i] - 1 - (i - best - 1 - 1)) / 2;
        if (best >= 0) {
            if (best == i - h[i] - 1) ans += pre[best + 1];
            else ans += res[best];
        }
        res.push_back(ans);
    }
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;

    while (T--) {
        cin >> N;
        h.clear();
        res.clear();

        ll pre[N + 1], minpre[N + 1];
        pre[0] = 0;
        minpre[0] = 1e18;

        for (int i = 0; i < N; i++) {
            ll hi; cin >> hi;
            h.push_back(hi);
            minpre[i + 1] = min(minpre[i], h[i] - i);
            pre[i + 1] = pre[i] + h[i];
        }
        
        // min basic spell to be able to explode whole side left of i (not including explode spell cost)
        ll left[N], right[N];
        calculate();
        for (int i = 0; i < N; i++) left[i] = res[i];

        res.clear();
        reverse(h.begin(), h.end());

        calculate();
        for (int i = 0; i < N; i++) right[N - i - 1] = res[i];
        reverse(h.begin(), h.end());

        ll best = 1e18;
        for (int i = 0; i < N; i++) best = min(best, h[i] + left[i] + right[i]);

        cout << best << endl;
    }
}