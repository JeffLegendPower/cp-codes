// https://open.kattis.com/problems/convexhull

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

typedef complex<double> pnt;
#define x real()
#define y imag()

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    pnt p1(3, 3);
    pnt p2(1, 5);

    // cout << arg(p2 - p1);

    while (true) {
        int N; cin >> N;
        if (N == 0) break;

        pnt points[N];
        pnt start(0, 1e4);
        for (int i = 0; i < N; i++) {
            double a, b; cin >> a >> b;
            points[i] = {a, b};
            if (points[i].y < start.y || (points[i].y == start.y && points[i].x > start.x)) {
                start = points[i];
            }
        }

        if (N == 1) {
            cout << 1 << endl;
            cout << start.x << " " << start.y << endl;
            continue;
        } if (N == 2) {
            cout << (1 + (points[1] != points[0])) << endl;
            cout << points[0].x << " " << points[0].y << endl;
            if (points[1] != points[0]) cout << points[1].x << " " << points[1].y << endl;
            continue;
        }

        sort(points, points + N, [start](pnt one, pnt two) {
            if (one == start) return false;
            if (two == start) return true;

            double slp1 = -(one.x - start.x) / (one.y - start.y + 0.000001);
            double slp2 = -(two.x - start.x) / (two.y - start.y + 0.000001);

            if (slp1 == slp2) return abs(one - start) < abs(two - start);

            return slp1 < slp2;
        });

        vector<pnt> hull;
        hull.push_back(start);
        hull.push_back(points[0]);
        for (int i = 1; i < N - 1; i++) {
            while (hull.size() >= 2) {
                double angle = remainder(arg(points[i] - hull.back()) - arg(hull[hull.size() - 2]-hull.back()), 2.0 * M_PI);
                if (angle >= 0) hull.pop_back();
                else break;
            }

            hull.push_back(points[i]);
        }

        cout << hull.size() << endl;
        for (int i = 0; i < hull.size(); i++) {
            cout << hull[i].x << " " << hull[i].y << endl;
        }
    }
}