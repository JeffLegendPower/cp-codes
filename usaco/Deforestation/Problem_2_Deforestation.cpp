// https://usaco.org/index.php?page=viewproblem&cpid=1435

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define plli pair<ll, int>
#define pll pair<ll, ll>
#define pii pair<int, int>

template<class T> using ordered_multiset = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct rng {
    ll l, r;
    int t;
};

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;

        ordered_multiset<ll> touse;
        ll x[N]; for (int i = 0; i < N; i++) {
            cin >> x[i];
            touse.insert(x[i]);
        }

        rng k[K];
        for (int i = 0; i < K; i++) cin >> k[i].l >> k[i].r >> k[i].t;
        sort(k, k + K, [](rng one, rng two) {
            if (one.r == two.r) return one.l < two.l;
            return one.r < two.r;
        });

        int rem = N;
        ordered_multiset<ll> oset;

        for (rng ki : k) {
            int t = ki.t;
            t -= oset.order_of_key(ki.l - 1);
            if (t <= 0) continue;

            while (t > 0) {
                auto cur = touse.lower_bound(ki.r);
                ll val = *cur;

                oset.insert(val);
                touse.erase(cur);

                t--;
                rem--;
            }
        }

        cout << rem;
        if (T > 0) cout << endl;
    }
}