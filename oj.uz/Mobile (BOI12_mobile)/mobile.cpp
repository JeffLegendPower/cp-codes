// https://oj.uz/problem/view/BOI12_mobile

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

#define pdd pair<double, double>

double dist2(pdd a, pdd b) {
	return (a.first - b.first) * (a.first - b.first)
	+ (a.second - b.second) * (a.second - b.second);
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
	ll L;
	cin >> N >> L;
 
	pdd s[N];
	for (int i = 0; i < N; i++) cin >> s[i].first >> s[i].second;
 
	double low = 0, high = 1e12;
	while (high - low > 0.000001) {
		double mid = low + (high - low) / 2;
 
		double x = 0;
		for (int i = 0; i < N; i++) {
			if (dist2({x, 0}, {s[i]}) > mid*mid) continue;
 
			// let x = s[i].first, y = s[i].second;
			// d^2 + y^2 = r^2
			// d = sqrt(r^2 - y^2)
            // let x2 be the current position
            // x2 = x + d
 
			x = s[i].first + sqrt(mid*mid - s[i].second * s[i].second);
		}

 
		if (x >= L) high = mid;
		else low = mid;
	}
 
	cout << fixed << setprecision(10) << high;
}