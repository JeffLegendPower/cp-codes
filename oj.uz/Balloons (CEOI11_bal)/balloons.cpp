// https://oj.uz/problem/view/CEOI11_bal

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    // let x be the radius of current balloon
    // let y be the radius of some previous balloon
    // let d be the distance between current balloon and some previous balloon

    // looking at just the current balloon with radius x and a previous balloon with radius y and the balloons are a distance d apart
    // we can create a triangle that relates x, y, and d assuming the 2 balloons touch
    // and get that (y-x)^2 + d^2 = (y+x)^2
    // y^2 - 2xy + x^2 + d^2 = y^2 + 2xy + x^2
    // d^2 = 4xy
    // x = d^2/4y
    // so now x is equal to the min of the max radius of the balloon and the min across all x = d^2/4y for all balloons before the current one

    // observation: if radius(j) > radius(k<j) then balloon j will be a better bounding balloon than balloon k

    int N; cin >> N;

    pdd b[N];
    for (int i = 0; i < N; i++) cin >> b[i].first >> b[i].second;

    cout << fixed << setprecision(3);

    double r[N];

    stack<int> s;
    for (int i = 0; i < N; i++) {
        r[i] = b[i].second;
        while (!s.empty()) {
            int j = s.top();
            r[i] = min(r[i], (b[i].first - b[j].first) * (b[i].first - b[j].first) / (4*r[j]));

            if (r[i] < r[j]) break;
            s.pop();
        }

        // we do like this because for all r[j] <= r[i] they won't be able to be bounding in the future so we can just test them
        // and remove from the stack. and for r[j] > r[i] we only need to look at that r[j] because for any k<j to be bounding
        if (!s.empty()) {
            int j = s.top();
            r[i] = min(r[i], (b[i].first - b[j].first) * (b[i].first - b[j].first) / (4*r[j]));
        }

        s.push(i);

        cout << r[i] << endl;
    }
}