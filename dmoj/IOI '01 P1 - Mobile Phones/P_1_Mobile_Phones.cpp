// https://dmoj.ca/problem/ioi01p1

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


template <class T, int... Ns> struct BIT {
	T val = 0;
	void upd(T v) { val += v; }
	T query() { return val; }
};

template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
	BIT<T, Ns...> bit[N + 1];
	template <typename... Args> void upd(int pos, Args... args) {
		for (; pos <= N; pos += (pos & -pos)) bit[pos].upd(args...);
	}
	template <typename... Args> T sum(int r, Args... args) {
		T res = 0;
		for (; r; r -= (r & -r)) res += bit[r].query(args...);
		return res;
	}
	template <typename... Args> T query(int l, int r, Args... args) {
		return sum(r, args...) - sum(l - 1, args...);
	}
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int S; cin >> S >> S;

    BIT<int, 1024, 1024> bit;

    while (true) {
        int t; cin >> t;

        if (t == 1) {
            int x, y, A; cin >> x >> y >> A;
            bit.upd(x+1, y+1, A);
        } if (t == 2) {
            int l, b, r, t; cin >> l >> b >> r >> t;
            cout << bit.query(l+1, r+1, b+1, t+1) << endl;
        } if (t == 3) break;
    }
}