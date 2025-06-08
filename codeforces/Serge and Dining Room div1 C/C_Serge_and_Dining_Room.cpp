// https://codeforces.com/contest/1179/problem/C

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
const int Nmax = 2e6;  // limit for array size
int N = 1048576;  // array size
int t[2 * Nmax];
int t2[2 * Nmax];

void modify(int p, int value) {  // set value at position p
    p += N;
    t[p] += value;
    t2[p] += value;
    for (; p > 1; p >>= 1) {
        t[p>>1] = t[p] + t[p^1];
        if (p&1) t2[p>>1] = max(t2[p], t2[p^1] + t[p]);
        else t2[p>>1] = max(t2[p^1], t2[p] + t[p^1]);
    }
}
// Segtree end


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int n, m; cin >> n >> m;

    ll a[n], b[m];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        modify(a[i], 1);
    } for (int i = 0; i < m; i++) {
        cin >> b[i];
        b[i]--;
        modify(b[i], -1);
    }

    int Q; cin >> Q;
    while (Q--) {
        int tp, i, x;
        cin >> tp >> i >> x;
        i--, x--;

        if (tp == 1) {
            modify(a[i], -1);
            a[i] = x;
            modify(a[i], 1);
        } else if (tp == 2) {
            modify(b[i], 1);
            b[i] = x;
            modify(b[i], -1);
        }

        if (t2[1] < 1) {
            cout << -1 << endl;
            continue;
        }

        int p = 1;
        int tot = 0;
        while ((p<<1) < 2*N) {

            int l = t2[p<<1] + t[(p<<1)|1];
            int r = t2[(p<<1)|1];
            if (r > -tot) p = (p<<1)|1;
            else {
                tot += t[p<<1|1];
                p = p<<1;
            }

            // cout << p << " " << l << " " << r << " " << tot << endl;
        }

        cout << p - N+1 << endl;
    }
}