// https://dmoj.ca/problem/ahscc1p5

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

struct etry {
    double a, n;
    int idx;
};

#define pdd pair<double, double>

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, K; cin >> N >> K;

    // (a + 1) / (n + 1) - a / n = (n - a) / (n(n + 1))
    // we can use this to order our elements to maximize our usage of our K points

    auto cmp = [](etry one, etry two) {
        double incrone = (one.n - one.a) / (one.n * (one.n + 1));
        double incrtwo = (two.n - two.a) / (two.n * (two.n + 1));

        // using a priority queue so gotta do it like this
        return incrone < incrtwo;
    };

    priority_queue<etry, vector<etry>, decltype(cmp)> pq(cmp);

    pdd grades[N];
    for (int i = 0; i < N; i++) cin >> grades[i].first;
    for (int i = 0; i < N; i++) {
        cin >> grades[i].second;
        pq.push({grades[i].first, grades[i].second, i});
    }

    while (K > 0) {
        K--;

        auto [a, n, idx] = pq.top(); pq.pop();
        grades[idx].first++;
        grades[idx].second++;

        pq.push({a + 1, n + 1, idx});
    }

    double total = 0;
    for (int i = 0; i < N; i++) total += grades[i].first / grades[i].second;

    total /= ((double) N);
    total *= 100;

    cout << fixed << setprecision(10) << total;
}