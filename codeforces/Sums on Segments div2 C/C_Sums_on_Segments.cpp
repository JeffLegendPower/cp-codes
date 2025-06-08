// https://codeforces.com/contest/2043/problem/C

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

        ll xpos = -1;
        ll a[N]; for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (abs(a[i]) != 1) xpos = i;
        }

        if (xpos == -1) {
            ll l = 0, h = 0;
            ll lans = 0, hans = 0;
            for (int i = N - 1; i >= 0; i--) {
                if (a[i] == 1) {
                    h = max(h + 1, 1ll);
                    l = min(l + 1, 1ll);
                } else {
                    l = min(l - 1, -1ll);
                    h = max(h - 1, -1ll);
                }

                lans = min(lans, l);
                hans = max(hans, h);
            }

            cout << hans - lans + 1 << endl;
            for (ll i = lans; i <= hans; i++) cout << i << " ";
            cout << endl;
            continue;
        }

        ll lansl = 0, hansl = 0;
        ll l = 0, h = 0;
        for (int i = xpos - 1; i >= 0; i--) {
            if (a[i] == 1) {
                h = max(h + 1, 1ll);
                l = min(l + 1, 1ll);
            } else {
                l = min(l - 1, -1ll);
                h = max(h - 1, -1ll);
            }

            lansl = min(lansl, l);
            hansl = max(hansl, h);
        }

        ll lansr = 0, hansr = 0;
        l = 0, h = 0;
        for (int i = xpos + 1; i < N; i++) {
            if (a[i] == 1) {
                h = max(h + 1, 1ll);
                l = min(l + 1, 1ll);
            } else {
                l = min(l - 1, -1ll);
                h = max(h - 1, -1ll);
            }

            lansr = min(lansr, l);
            hansr = max(hansr, h);
        }

        vector<int> nums;
        for (ll i = min(lansl, lansr); i <= max(hansl, hansr); i++) nums.push_back(i);

        ll low = 0, high = 0;
        ll s = 0;
        for (int i = xpos - 1; i >= 0; i--) {
            s += a[i];
            low = min(low, s);
            high = max(high, s);
        }

        s = 0;
        ll low2 = 0, high2 = 0;
        for (int i = xpos + 1; i < N; i++) {
            s += a[i];
            low2 = min(low2, s);
            high2 = max(high2, s);
        }

        for (ll i = a[xpos] + low + low2; i <= a[xpos] + high + high2; i++) nums.push_back(i);
        sort(nums.begin(), nums.end());

        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (i < nums.size() - 1 && nums[i] == nums[i + 1]) continue;
            ans.push_back(nums[i]);
        }

        cout << ans.size() << endl;
        for (int k : ans) cout << k << " ";
        cout << endl;
    }
}