// https://codeforces.com/contest/1997/problem/E

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
const int Nmax = 4e5;  // limit for array size
int N = 262144;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, q; cin >> n >> q;

    vector<vector<int>> lvls(2e5 + 1);
    int a[n]; for (int i = 0; i < n; i++) {
        cin >> a[i];
        lvls[a[i]].push_back(i);
        t[N + i] = 1;
    }
    build();

    vector<vector<int>> ups(n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (ups[j].size() < i - 1) break;

            int st = ups[j].empty() ? 0 : (ups[j].back() + 1);
            if (st >= n) break;
            
            int low = st, high = N - 1;
            int best = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (query(st, mid+1) >= j) {
                    high = mid - 1;
                    best = mid;
                } else low = mid + 1;
            }

            if (best == -1) break;
            ups[j].push_back(best);
        }

        for (int idx : lvls[i]) modify(idx, 0);
    }

    while (q--) {
        int i, x;
        cin >> i >> x;
        i--;

        int lvl = a[i];

        if (ups[x].size() < lvl) {
            cout << "YES" << endl;
            continue;
        }

        int st = ups[x][lvl - 1];
        if (st >= i) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}