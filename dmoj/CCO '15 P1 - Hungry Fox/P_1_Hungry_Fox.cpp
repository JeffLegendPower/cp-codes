// https://dmoj.ca/problem/cco15p1

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    ll W;
    cin >> N >> W;

    vector<ll> below, above, mid;
    for (int i = 0; i < N; i++) {
        ll a; cin >> a;
        if (a < W) below.push_back(a);
        else if (a > W) above.push_back(a);
        else mid.push_back(a);
    }

    sort(below.begin(), below.end());
    sort(above.begin(), above.end(), greater<ll>());
    ll minn = 0;
    if (!below.empty()) minn += W - below[0];
    if (!above.empty()) minn += above[0] - W;

    ll most = 0;
    int l = 0, r = 0;
    vector<ll> order;
    if (below.size() > above.size()) {
        order.push_back(below[0]);
        l++;
    }

    while (l < below.size() && r < above.size()) {
        order.push_back(above[r++]);
        order.push_back(below[l++]);

        if (r == above.size() && !mid.empty()) {
            above.push_back(mid.back());
            mid.pop_back();
        } if (l == below.size() && !mid.empty()) {
            below.push_back(mid.back());
            mid.pop_back();
        }
    }

    if (r < above.size()) {
        order.push_back(above[r++]);
    }

    ll summ = 0;
    if (!order.empty()) summ += abs(W - order[0]);
    for (int i = 1; i < order.size(); i++) {
        summ += abs(order[i] - order[i - 1]);
    }

    vector<ll> finish;
    while (l < below.size()) finish.push_back(abs(W - below[l++]));
    while (r < above.size()) finish.push_back(abs(W - above[r++]));
    while (!mid.empty()) {
        finish.push_back(0);
        mid.pop_back();
    }

    sort(finish.begin(), finish.end());
    if (finish.empty()) {
        cout << minn << " " << summ << endl;
        return 0;
    }

    l = 0, r = finish.size() - 1;
    summ += max(abs(W - order.back()) - finish[l], finish[l]);
    l++;

    while (r > l) {
        ll pos = finish[r--];
        summ += pos;

        summ += max(pos - finish[l], finish[l]);
        l++;
    }

    if (l == r) summ += finish[r];

    cout << minn << " " << summ << endl;
}