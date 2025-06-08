// https://usaco.org/index.php?page=viewproblem&cpid=1439

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

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;

        pll js[N];
        for (int i = 0; i < N; i++) cin >> js[i].first >> js[i].second;

        // This made me feel like a genius
        // I want an optimal ordering of my jobs so I can solve this greedily
        // assume current time is x and s[i], s[j] >= x

        // for job i to go before job j
        // x + t[i] <= s[j] and x + t[j] > s[i]
        // With some math we get that s[i] + t[i] <= s[j] + t[j]

        // If this ingenius logic is still wrong ima crash out
        sort(js, js + N, [](pll one, pll two) {
            if (one.first + one.second == two.first + two.second) return one.first < two.first;
            return one.first + one.second <= two.first + two.second;
        });

        int jobs = 0;
        ll time = 0;
        priority_queue<ll> torem;
        for (int i = 0; i < N; i++) {
            auto [s, t] = js[i];

            if (time <= s) {
                time += t;
                jobs++;
            } else {
                // Not worth adding as we would be increasing total time taken for no more jobs
                if (torem.top() < t) continue;
                // Not worth adding as we would have to remove >1 jobs just to fit this one job in
                if (time - torem.top() > s) continue;

                // Now worth replacing the most time consuming job already taken with this job
                // to minimize our time
                time += t - torem.top();
                torem.pop();
            }

            torem.push(t);
        }

        cout << jobs;
        if (T > 0) cout << endl;
    }
}