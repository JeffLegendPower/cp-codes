// https://usaco.org/current/index.php?page=viewproblem&cpid=1437

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
const int Nmax = 2e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

void modify(int l, int r, int value) {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l&1) t[l++] += value;
        if (r&1) t[--r] += value;
    }
}

int query(int p) {
    int res = 0;
    for (p += N; p > 0; p >>= 1) res += t[p];
    return res;
}
// Segtree end

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    int a[N];
    vector<int> vals[N];

    for (int i = 0; i < N; i++) {
        int inp = 0;
        cin >> inp;
        a[i] = inp - 1;
        vals[inp - 1].push_back(i);
    }

    for (int i = 0; i < N; i++) {
        ll d = 0;
        while (d < N) {

            ll next_d = 1e18;


            int j = 0;
            int groups = 0;


            while (j < vals[i].size()) {
                int val = vals[i][j];

                int mx = val + d + 1;
                groups++;

                int low = 0, high = vals[i].size() - 1;
                int best = -1;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    if (vals[i][mid] <= mx) low = mid + 1;
                    else {
                        high = mid - 1;
                        best = mid;
                    }
                }

                if (best == -1) break;

                j = best;

                next_d = min<ll>(next_d, vals[i][best] - val - 1);
            }

            if (next_d == 1e18) {
                modify(d, N, groups);
                break;
            }
            else {
                modify(d, next_d, groups);
            }

            d = next_d;
        }
    }

    for (int i = 0; i < N; i++) {
        cout <<  query(i) << endl;
    }
}