// https://oj.uz/problem/view/NOI22_gymbadges

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
    
    int N; cin >> N;

    pll gyms[N];
    for (int i = 0; i < N; i++) cin >> gyms[i].first;
    for (int i = 0; i < N; i++) cin >> gyms[i].second;

    // sort such that at worst going thru gym i<j will result in a lower lvl than going through gym j>i
    sort(gyms, gyms + N, [](pll one, pll two) {
        return (one.first + one.second) < (two.first + two.second);
    });

    int num = 0;
    ll lvl = 0;
    priority_queue<ll> used;
    for (auto [X, L] : gyms) {
        if (lvl <= L) {
            lvl += X;
            num++;
            used.push(X);
        }

        // if cant increase # gyms, then minimize lvl
        // and we can guarantee a replace because notice that for the j that we are replacing with i
        // X[j] > X[i] and X[j] + L[j] < X[i] + L[i], so L[j] < L[i] which means we will always be able to replace
        else if (!used.empty() && used.top() > X) {
            lvl -= used.top();
            lvl += X;

            used.pop();
            used.push(X);
        }
    }

    cout << num;
}