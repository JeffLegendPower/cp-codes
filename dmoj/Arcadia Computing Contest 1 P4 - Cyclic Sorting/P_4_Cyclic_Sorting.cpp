// https://dmoj.ca/problem/ahscc1p4

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

    int N, Q; cin >> N >> Q;

    // cmp[i] = true if a[i] > a[i + 1] for i < N - 1
    // and cmp[N - 1] = true if a[N - 1] > a[0]
    bool cmps[N];
    ll a[N]; for (int i = 0; i < N; i++) cin >> a[i];

    set<int> mores;
    for (int i = 0; i < N - 1; i++) {
        cmps[i] = a[i] > a[i + 1];
        if (cmps[i]) mores.insert(i);
    } cmps[N - 1] = a[N - 1] > a[0];
    if (cmps[N - 1]) mores.insert(N - 1);

    while (Q--) {
        int i; ll x;
        cin >> i >> x;
        i--;
        a[i] = x;

        if (i > 0) {
            if (cmps[i - 1]) mores.erase(i - 1);
            cmps[i - 1] = a[i - 1] > a[i];
            if (cmps[i - 1]) mores.insert(i - 1);
        } else {
            if (cmps[N - 1]) mores.erase(N - 1);
            cmps[N - 1] = a[N - 1] > a[i];
            if (cmps[N - 1]) mores.insert(N - 1);
        }

        if (cmps[i]) mores.erase(i);
        cmps[i] = a[i] > a[(i + 1)%N];
        if (cmps[i]) mores.insert(i);

        if (mores.size() > 1) cout << -1 << endl;
        else if (mores.size() == 0) cout << 0 << endl;
        else {
            int idx = *mores.begin();
            int dist = N - 1 - idx;
            dist = min(dist, idx + 1);
            cout << dist << endl;
        }
    }
}