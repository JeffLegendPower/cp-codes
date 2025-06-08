// https://dmoj.ca/problem/ioi07p1

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

bool query(ll x, ll y) {
    cout << "examine " << x << " " << y << endl;
    string ress; cin >> ress;
    return ress == "true";
}

ll rundir(ll x0, ll y0, ll N, function<pll(ll, ll, ll)> upd) {
    int b = 0;
    ll dist = 0;
    for (; b <= 30; b++) {
        auto [x2, y2] = upd(x0, y0, 1ll<<b);

        if (x2 < 1 || x2 > N || y2 < 1 || y2 > N) {
            dist += (1ll<<b)/2;
            
            auto [x3, y3] = upd(x0, y0, (1ll<<b)/2);
            x0 = x3;
            y0 = y3;

            b--;
            break;
        }

        bool res = query(x2, y2);

        if (res) continue;
        dist += (1ll<<b)/2;

        auto [x3, y3] = upd(x0, y0, (1ll<<b)/2);
        x0 = x3;
        y0 = y3;

        b--;
        break;
    }

    for (int b2 = b-1; b2 >= 0; b2--) {
        auto [x2, y2] = upd(x0, y0, 1ll<<b2);

        if (x2 < 1 || x2 > N || y2 < 1 || y2 > N) continue;

        bool res = query(x2, y2);

        if (!res) continue;
        dist += (1ll<<b2);
        
        auto [x3, y3] = upd(x0, y0, 1ll<<b2);
        x0 = x3;
        y0 = y3;
    }

    return dist;
}

void solve(ll N, ll x0, ll y0) {
    ll M = rundir(x0, y0, N, [](ll x, ll y, ll d) {
        pll res = {x+d, y};
        return res;
    }) + 1;

    ll modx = rundir(x0, y0, N, [](ll x, ll y, ll d) {
        pll res = {x-d, y};
        return res;
    }); M += modx;

    ll mody = rundir(x0, y0, N, [](ll x, ll y, ll d) {
        pll res = {x, y-d};
        return res;
    });

    x0 += M/2 - modx;
    y0 += M/2 - mody;
    
    // move coord to top right tile
    while (true) {
        ll x2 = x0 + M, y2 = y0 + M;
        if (x2 < 1 || x2 > N || y2 < 1 || y2 > N) break;
        bool res = query(x2, y2);

        if (!res) break;
        x0 += M;
        y0 += M;
    }
    while (true) {
        ll x2 = x0 + 2*M, y2 = y0;
        if (x2 < 1 || x2 > N || y2 < 1 || y2 > N) break;
        bool res = query(x2, y2);

        if (!res) break;
        x0 += 2*M;
    }
    while (true) {
        ll x2 = x0, y2 = y0 + 2*M;
        if (x2 < 1 || x2 > N || y2 < 1 || y2 > N) break;
        bool res = query(x2, y2);

        if (!res) break;
        y0 += 2*M;
    }

    cout << "solution " << x0 - 2*M << " " << y0 - 2*M << endl;
}
    
int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    ll N, x0, y0;
    cin >> N >> x0 >> y0;
    
    solve(N, x0, y0);
}