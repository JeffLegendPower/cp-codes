// https://codeforces.com/contest/2046/problem/C

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

ordered_multiset above, below;

pll bsearch() {
    ll low = 1, high = min(above.size(), below.size());
    ll best = 0;
    ll bestx = -1;
    while (low <= high) {
        ll m = low + (high - low) / 2;

        ll l1 = above.find_by_order(m - 1)->first + 1;
        ll r1 = above.find_by_order(above.size() - m)->first;

        ll l2 = below.find_by_order(m - 1)->first + 1;
        ll r2 = below.find_by_order(below.size() - m)->first;

        if (max(l1, l2) <= min(r1, r2)) {
            low = m + 1;
            best = m;
            bestx = max(l1, l2);
        } else high = m - 1;
    }

    return {best, bestx};
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        above.clear();
        below.clear();

        pll cts[N]; for (int i = 0; i < N; i++) cin >> cts[i].first >> cts[i].second;
        sort(cts, cts + N, [](pll one, pll two) {
            return one.second > two.second;
        });

        ll best = 0;
        pll bcoords = {-1e9, -1e9};
        for (int i = 0; i < N; i++) below.insert({cts[i].first, i});
        for (int i = 0; i < N; i++) {
            below.erase({cts[i].first, i});
            above.insert({cts[i].first, i});
            if (i < N - 1 && cts[i].second == cts[i + 1].second) continue;

            auto [ans, x] = bsearch();
            if (ans > best) {
                best = ans;
                bcoords = {x, cts[i].second};
            }
        }

        cout << best << endl << bcoords.first << " " << bcoords.second << endl;
    }
}