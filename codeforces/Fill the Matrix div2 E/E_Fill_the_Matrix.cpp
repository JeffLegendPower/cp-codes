// https://codeforces.com/problemset/problem/1841/E

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;

    while (T--) {
        ll N; cin >> N;

        vector<int> idxs(N + 2);
        pii a[N];
        for (int i = 0; i < N; i++) {
            cin >> a[i].first;
            a[i].second = i;
        } sort(a, a + N, greater<pii>());

        ll m; cin >> m;

        vector<ll> cnts(N + 1, 0);

        // end idx, {first (lowermost) idx this range was added, start idx}
        map<int, plli> segs;
        segs[N - 1] = {N, 0};
        for (auto [ai, i] : a) {
            auto itr = segs.lower_bound(i);
            int start = itr->second.second, end = itr->first;
            ll num = itr->second.first;

            cnts[end - start + 1] += num - ai;

            segs.erase(itr);
            if (i > start) segs[i - 1] = {ai, start};
            if (i < end) segs[end] = {ai, i + 1};
        }

        ll total = 0;
        for (ll i = N; i >= 1; i--) {
            if (m / i < cnts[i]) {
                total += m;
                total -= (m + i - 1) / i;
                break;
            }

            ll num = cnts[i];
            total += num * (i - 1);
            m -= num * i;
        }

        cout << total << endl;
    }
}