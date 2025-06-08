// https://usaco.org/index.php?page=viewproblem&cpid=1488

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N; cin >> N;

    ll a[N]; 
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    for (int l = 0; l < N; l++) {
        ll maxx = 0, maxx2 = 0;
        for (int r = l; r < N; r++) {
            maxx = max(maxx, a[r]);
            if (r > l) maxx2 = max(maxx2, min(a[r], a[r-1]));

            // if (r-l+1 == 3) ans += max(a[l], a[r]);
            else    if (r-l+1 == 4) ans += max(min(a[l], a[l+1]), min(a[r-1], a[r]));
            // else if ((r-l+1)&1) ans += maxx;
            // else ans += maxx2;

            // cout << a[r] << endl;

            // if ((r-l+1) == 5) ans += maxx;
        }
    }

    cout << ans;
}